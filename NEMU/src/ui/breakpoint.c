#include "ui/breakpoint.h"

#include "nemu.h"

#define NR_BP 32

uint32_t expr(const char*,bool*);

static BP bp_pool[NR_BP];
static BP *head, *free_;
static WP *wp_head;

extern int nemu_state;

void init_bp_pool() {
	int i;
	for(i = 0; i < NR_BP - 1; i ++) {
		bp_pool[i].NO = i;
		bp_pool[i].next = &bp_pool[i + 1];
	}
	bp_pool[i].NO = i;
	bp_pool[i].next = NULL;

	head = NULL;wp_head = NULL;
	free_ = bp_pool;
}

/* TODO: Implement the function of breakpoint */

BP* new_bp() {
	if (free_ == NULL) return NULL;
	BP* p = free_;
	free_ = free_->next;
	p->next = head;
	head = p;
	p->count = 0;
	return head;
}

bool free_bp(BP* bp) {
	if (bp != head) {
		BP* p = head;
		while ((p != NULL)&&(p->next != bp))
			p = p->next;
		if (p == NULL) return 0;
		p->next = bp->next;
	} else {
		head = head->next;
	}
	bp->next = free_;
	free_ = bp;
	return 1;
}

void set_bp(BP* bp) {
	bp->code = swaddr_read(bp->addr,1);
	swaddr_write(bp->addr,1,INT3_CODE);
}
void reset_bp(BP* bp) {
	swaddr_write(bp->addr,1,bp->code);
}

BP*  get_bp(swaddr_t addr) {
	BP* p = head;
	while ((p != NULL)&&(p->addr != addr))
		p = p->next;
	return p;
}

void load_breakpoint() {
	BP* p;
	for (p = head;p != NULL;p = p->next) {
		set_bp(p);
		p->count = 0;
	}
	for (p = wp_head;p != NULL;p = p->next)
		p->count = 0;
}

WP* new_wp() {
	if (free_ == NULL) return NULL;
	WP* p = free_;
	free_ = free_->next;
	p->next = wp_head;
	wp_head = p;
	p->count = 0;
	return wp_head;
}

bool free_wp(WP* wp) {
	if (wp != wp_head) {
		WP* p = wp_head;
		while ((p != NULL)&&(p->next != wp))
			p = p->next;
		if (p == NULL) return 0;
		p->next = wp->next;
	} else {
		wp_head = wp_head->next;
	}
	wp->next = free_;
	free_ = wp;
	return 1;
}

void delete_all() {
	while (head != NULL) {
		reset_bp(head);
		free_bp(head);
	}
	while (wp_head != NULL) free_wp(wp_head);
	puts("All breakpoints and watchpoints deleted.");
}
void delete_bp(int NO) {
	if ((NO >= 0)&&(NO < NR_BP)) {
		if (free_bp(bp_pool+NO)) {
			reset_bp(bp_pool+NO);
			printf("Breakpoint %d deleted.\n",NO);
			return;
		}
		if (free_wp(bp_pool+NO)) {
			printf("Watchpoint %d deleted.\n",NO);
			return;
		}
	}
	printf("Breakpoint or watchpoint %d doesn't exist.\n",NO);
}

bool check_wp() {
	if (wp_head == NULL) return false;
	hide_bp();
	bool ok = false;
	WP* p = wp_head;
	while (p != NULL) {
		bool success = true;
		uint32_t t = expr(p->expr,&success);
		if (t != p->value) {
			printf("\nWatchpoint %d: %s\n",p->NO,p->expr);
			printf("Old value = %u\n",p->value);
			printf("New value = %u\n",t);
			p->value = t;
			p->count++;
			ok = true;
		}
		p = p->next;
	}
	show_bp();
	return ok;
}

void print_bp() {
	if ((head == NULL)&&(wp_head == NULL)) {
		puts("No breakpoints or watchpoints.");
		return;
	}
	printf("No\tType\t\tAddress\t\tWhat\n");
	BP* p = head;
	while (p != NULL) {
		printf("%d\tbreakpoint\t0x%08x\n",p->NO,p->addr);
		if (p->count > 0)
			printf("\tbreakpoint already hit %d time\n",p->count);
		p = p->next;
	}
	p = wp_head;
	while (p != NULL) {
		printf("%d\twatchpoint\t\t\t%s\n",p->NO,p->expr);
		if (p->count > 0)
			printf("\twatchpoint already hit %d time\n",p->count);
		p = p->next;
	}
}

void hide_bp() {
	BP* p;
	for (p = head;p != NULL;p = p->next) {
		p->tmp = swaddr_read(p->addr,1);
		swaddr_write(p->addr,1,p->code);
	}
}
void show_bp() {
	BP* p;
	for (p = head;p != NULL;p = p->next)
		swaddr_write(p->addr,1,p->tmp);
}
