#include "ui/ui.h"
#include "ui/breakpoint.h"

#include "nemu.h"

#include <signal.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int nemu_state = END;
extern uint8_t loader [];
#define LOADER_START 0x100000

void cpu_exec(uint32_t);
void restart();

void print_bp();

uint32_t expr(const char*,bool*);

/* We use the readline library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;

	if (line_read) {
		free(line_read);
		line_read = NULL;
	}

	line_read = readline("(nemu) ");

	if (line_read && *line_read) {
		add_history(line_read);
	} else if (history_length) {
		if (line_read) free(line_read);
		char *p = previous_history()->line;
		line_read = (char*)malloc(strlen(p)+1);
		strcpy(line_read,p);
	}

	return line_read;
}

/* This function will be called when you press <C-c>. And it will return to 
 * where you press <C-c>. If you are interesting in how it works, please
 * search for "Unix signal" in the Internet.
 */
static void control_C(int signum) {
	if(nemu_state == RUNNING) {
		nemu_state = INT;
	}
}

void init_signal() {
	/* Register a signal handler. */
	struct sigaction s;
	memset(&s, 0, sizeof(s));
	s.sa_handler = control_C;
	int ret = sigaction(SIGINT, &s, NULL);
	assert(ret == 0);
}

static void cmd_c() {
	if(nemu_state == END) {
		puts("The Program does not start. Use 'r' command to start the program.");
		return;
	}

	cpu_exec(-1);
}

static void cmd_r() {
	if(nemu_state != END) { 
		char c;
		while(1) {
			printf("The program is already running. Restart the program? (y or n)");
			fflush(stdout);
			scanf(" %c", &c);
			switch(c) {
				case 'y': goto restart_;
				case 'n': return;
				default: puts("Please answer y or n.");
			}
		}
	}

restart_:
	restart();
	nemu_state = RUNNING;
	cmd_c();
}

static void cmd_si(const char* s) {
	int N;
	if (sscanf(s,"%d",&N) == 0) {
		printf("No symbol \"%s\" in current context.\n",s);
		return ;
	}
	if (N < 0) return;
	if(nemu_state == END) { 
		restart();
		nemu_state = RUNNING;
	}
	cpu_exec(N);
}

static void cmd_info(const char* s) {
	if (strcmp(s,"r") == 0) {
		int i;
		for (i = R_EAX;i <= R_EDI;i++) {
			printf("%s\t\t0x%x\t",regsl[i],reg_l(i));
			if (regsl[i][2] == 'p')
				printf("0x%x\n",reg_l(i));
			else printf("%d\n",reg_l(i));
		}
		printf("eip\t\t0x%x\t0x%x\n",cpu.eip,cpu.eip);
	} else if (strcmp(s,"b") == 0) {
		print_bp();
	} else puts("Please confirm the arguement,r or b.");
}

static void cmd_x(const char* s,const char* EXPR) {
	hide_bp();
	int i,j,N;
	if (sscanf(s,"%d",&N) < 1) {
		puts("Please confirm the arguement.");
		return;
	}
	bool success = true;
	swaddr_t addr = expr(EXPR,&success);
	if (success) {
		for (i = 0;i < N;i += 4) {
			printf("0x%08x:\t",addr+i*4);
			for (j = 0;(j < 4)&&(i+j < N);j++)
				printf(" 0x%08x",swaddr_read(addr+(i+j)*4,4));
			printf("\n");
		}
	} else puts("Illegal expression.");
	show_bp();
}

static void cmd_b(const char* EXPR) {
	if (EXPR[0] != '*') {
		puts("Please confirm the arguement.");
		return;
	}
	bool success = true;
	swaddr_t addr = expr(EXPR+1,&success);
	if (success) {
		if (get_bp(addr) != NULL) {
			puts("Already a breakpoint here.");
			return;
		}
		BP* bp = new_bp();
		if (bp == NULL) {
			puts("Too many breakpoint or watchpoint.");
			return;
		}
		bp->addr = addr;
		bp->code = swaddr_read(addr,1);
		set_bp(bp);
		printf("Breakpoint %d at 0x%08x.\n",bp->NO,addr);
	} else puts("Illegal expression.");
}

static void cmd_d(const char* s) {
	if (s == NULL) {
		char c;
		while(1) {
			printf("Delete all breakpoints and watchpoints? (y or n)");
			fflush(stdout);
			scanf(" %c", &c);
			switch(c) {
				case 'y': delete_all();
				case 'n': return;
				default: puts("Please answer y or n.");
			}
		}
	} else {
		int N;
		if (sscanf(s,"%d",&N) == 0) {
			printf("No symbol \"%s\" in current context.\n",s);
			return ;
		}
		delete_bp(N);
	}

}

static void cmd_p(const char* EXPR) {
	hide_bp();
	if (EXPR == NULL) {
		puts("Please input the expression.");
	} else {
		bool success = true;
		uint32_t result = expr(EXPR,&success);
		if (success) printf("%#x\t%u\n",result,result);
		else puts("Illegal expression.");
	}
	show_bp();
}

static void cmd_w(const char* EXPR) {
	hide_bp();
	if (EXPR == NULL) {
		puts("Please input the expression.");
		return;
	}
	bool success = true;
	uint32_t result = expr(EXPR,&success);
	if (success) {
		WP* wp = new_wp();
		if (wp == NULL) {
			puts("Too many breakpoint or watchpoint.");
			return;
		}
		strcpy(wp->expr,EXPR);
		wp->value = result;
		printf("Watchpoint %d: %s\nNow equal to %u\n",wp->NO,wp->expr,result);
	} else puts("Illegal expression.");
	show_bp();
}

void main_loop() {
	char *cmd;
	while(1) {
		cmd = rl_gets();
		char *p = strtok(cmd, " ");

/*		if((p == NULL)&&(history_length > 0)) {
			remove_history(history_length);
			cmd = (char*)malloc(strlen(history_get(history_length)->line));
			strcpy(cmd,history_get(history_length)->line);
			p = strtok(cmd, " ");
		}*/
		if(p == NULL) { continue; }

		if(strcmp(p, "c") == 0) { cmd_c(); }
		else if(strcmp(p, "r") == 0) { cmd_r(); }
		else if(strcmp(p, "q") == 0) { return; }
		else if(strcmp(p, "si") == 0) { 
			p = strtok(NULL, " ");
			if (p == NULL) p = "1";
			cmd_si(p);
		}
		else if(strcmp(p, "info") == 0) {
			p = strtok(NULL, " ");
			if (p == NULL) p = "";
			cmd_info(p);
		}
		else if(strcmp(p, "x") == 0) {
			p = strtok(NULL, " ");
			char *p1 = strtok(NULL, "");
			if (p == NULL) p = "";
			if (p1 == NULL) p1 = "";
			cmd_x(p,p1);
		}
		else if (strcmp(p, "b") == 0) {
			p = strtok(NULL, "");
			if (p == NULL) p = "";
			cmd_b(p);
		}
		else if (strcmp(p, "d") == 0) {
			p = strtok(NULL, " ");
			cmd_d(p);
		}
		else if (strcmp(p, "p") == 0) {
			p = strtok(NULL, "");
			cmd_p(p);
		}
		else if (strcmp(p, "w") == 0) {
			p = strtok(NULL, "");
			cmd_w(p);
		}

		/* TODO: Add more commands */

		else { printf("Unknown command '%s'\n", p); }
	}
}
