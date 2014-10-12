#include "common.h"
#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum {
	NOTYPE = 256,
	EQ,NE,LE,GE,
	AND,OR,NOT,SAL,SAR,
	NUM,HNUM,REG,
	NEG,
	DEREF
	/* TODO: Add more token types */

};

static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{" +",	NOTYPE},				// white space
	{"\\+", '+'},					// plus
	{"-", '-'},						// subtract
	{"\\*", '*'},					// multiply
	{"/", '/'},						// divid
	{"%", '%'},						// modulo
	{"<<", SAL},					// left shift
	{">>", SAR},					// right shift
	{"<=", LE},						// less or equal
	{">=", GE},						// greater or equal
	{"==", EQ},						// equal
	{"!=", NE},						// not equal
	{"<", '<'},						// less
	{">", '>'},						// greater
	{"&&", AND},					// logical and
	{"\\|\\|", OR},					// logical or
	{"!", NOT},						// logical not
	{"&", '&'},						// bitwise and
	{"\\|", '|'},					// bitwise or
	{"\\^", '^'},					// bitwise xor
	{"~", '~'},						// bitwise not
	{"\\(", '('},					// left bracket
	{"\\)", ')'},					// right bracket
	{"0[xX][[:xdigit:]]+", HNUM},	// hexadecimal number
	{"[[:digit:]]+", NUM},			// number
	{"\\$[[:alpha:]]+", REG}		// register
};
int level(int type) {
	int result = 100;
	switch (type) {
		case NEG: case '~': case NOT: case DEREF:
			result = 16; break;
		case '*': case '/': case '%':
			result = 14; break;
		case '+': case '-':
			result = 13; break;
		case SAL: case SAR:
			result = 12; break;
		case '<': case LE: case '>': case GE:
			result = 11; break;
		case EQ: case NE:
			result = 10; break;
		case '&':
			result = 9; break;
		case '^':
			result = 8; break;
		case '|':
			result = 7; break;
		case AND:
			result = 6; break;
		case OR:
			result = 5; break;
	}
	return result;
}

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for more times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			test(0, "regex compilation failed: %s\n%s\n", error_msg, rules[i].regex);
		}
	}
}

typedef struct token {
	int type;
	char str[32];
} Token;

Token tokens[100];
int nr_token;

static bool make_token(const char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	
	nr_token = 0;

	while(e[position] != '\0') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				const char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;

				//Log("match regex[%d] at position %d with len %d: %.*s", i, position, substr_len, substr_len, substr_start);

				position += substr_len;


				/* TODO: Now a new token is recognized with rules[i]. 
				 * Add codes to perform some actions with this token.
				 */

				switch(rules[i].token_type) {
					case NOTYPE:
						break;
					case NUM: case HNUM: case REG:
						strncpy(tokens[nr_token].str,substr_start,substr_len);
						tokens[nr_token].str[substr_len] = 0;
					default:
						tokens[nr_token].type = rules[i].token_type;
						nr_token++;
				}

				break;
			}
		}

		if(i == NR_REGEX) {
			//printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}

	return true; 
}

bool check_parentheses(int p,int q,bool* success) {
	int i,cnt = 0;
	bool ok = (tokens[p].type == '(')&&(tokens[q].type == ')');
	for (i = p;i <= q;i++) {
		if (tokens[i].type == '(') cnt++;
		if (tokens[i].type == ')') cnt--;
		if ((cnt == 0)&&(i < q)) ok = false;
		if (cnt < 0) *success = false;
	}
	if (cnt != 0) *success = false;
	return ok&&(*success);
}
int dominant(int p,int q) {
	int i,cnt = 0,result = -1;
	for (i = p;i <= q;i++) {
		switch (tokens[i].type) {
			case '(': cnt++;break;
			case ')': cnt--;break;
			case NUM: case HNUM: case REG: break;
			default:
				if (cnt == 0) {
					if (result < 0) result = i;
					if (level(tokens[i].type) == level(tokens[result].type))
						switch (tokens[i].type) {
							case '~': case NOT: case NEG: case DEREF:
								break;
							default:
								result = i;
						}
					if (level(tokens[i].type) < level(tokens[result].type))
						result = i;

				}
		}
	}
	return result;
}

uint32_t eval(int p,int q,bool *success) {
	if (p > q) {
		/* Bad expression */
		*success = false;
		return 0;
	}
	else if (p == q) { 
		/* Single token.
		 * For now this token should be a number. 
		 * Return the value of the number.
		 */
		uint32_t x = 0;
		int i;
		switch (tokens[p].type) {
			case NUM:
				sscanf(tokens[p].str,"%d",&x);
				return x;
			case HNUM:
				sscanf(tokens[p].str,"%x",&x);
				return x;
			case REG:
				//Log("%s",tokens[p].str);
				for (i = R_EAX;i <= R_EDI;i++)
					if (strcasecmp(regsl[i],tokens[p].str+1) == 0)
						return reg_l(i);
				for (i = R_AX;i <= R_DI;i++)
					if (strcasecmp(regsw[i],tokens[p].str+1) == 0)
						return reg_w(i);
				for (i = R_AL;i <= R_BH;i++)
					if (strcasecmp(regsb[i],tokens[p].str+1) == 0)
						return reg_b(i);
				if (strcasecmp("eip",tokens[p].str+1) == 0)
					return cpu.eip;
				break;
		}
		*success = false;
		return x;
	}
	else if (check_parentheses(p,q,success)) {
		/* The expression is surrounded by a matched pair of parentheses. 
		 * If that is the case, just throw away the parentheses.
		 */
		return eval(p+1,q-1,success); 
	}
	else if (*success) {
		int op = dominant(p,q);
		uint32_t val1 = (op == p)?0:eval(p,op-1,success);
		uint32_t val2 = eval(op+1,q,success);
		switch (tokens[op].type) {
			case NOT: case '~':
				if (op != p) {
					*success = false;
					return 0;
				}
		}
		switch (tokens[op].type) {
			case '+': return val1+val2;
			case '-': return val1-val2;
			case '*': return val1*val2;
			case '/': return val1/val2;
			case '%': return val1%val2;
			case '<': return val1 < val2;
			case '>': return val1 > val2;
			case LE:  return val1 <= val2;
			case GE:  return val1 >= val2;
			case EQ:  return val1 == val2;
			case NE:  return val1 != val2;
			case AND: return val1&&val2;
			case OR:  return val1||val2;
			case NOT: return !val2;
			case SAL: return val1<<val2;
			case SAR: return val1>>val2;
			case '&': return val1&val2;
			case '|': return val1|val2;
			case '^': return val1^val2;
			case '~': return ~val2;
			case NEG: return -val2;
			case DEREF:return swaddr_read(val2,4);
			default:
				*success = false;
				return 0;
		}
	}
	else return 0;
}

bool check(int type) {
	if (type == NUM) return true;
	if (type == HNUM) return true;
	if (type == REG) return true;
	if (type == ')') return true;
	return false;
}

uint32_t expr(const char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
	}

	/* TODO: Implement code to evaluate the expression. */
	int i;
	for (i = 0; i < nr_token; i ++) {
		if ((i == 0)||(!check(tokens[i-1].type))) {
			if (tokens[i].type == '-')
				tokens[i].type = NEG;
			if (tokens[i].type == '*')
				tokens[i].type = DEREF;
		}
	}
	return eval(0,nr_token-1,success);
}

