/***************************************************
 * word.c
 * do several count jobs, work with stdin & stdout
 * Author: nettee
 * Version: 0.4.4
 * Date: 2013.11.04
 *************************************************/

int is_alpha(char c);
int is_digit(char c);
int is_lower(char c);
int is_upper(char c);
int to_lower(char c);
int to_upper(char c);

int atoi(char * s);
int ishex(char c);
int hctoi(char c);
int ihtoi(char * s);

long character_count(void);
long line_count(void);
long blank_count(void);

void rm_unneeded_blank(void);
