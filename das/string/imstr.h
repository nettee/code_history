#include <stdio.h>
#include <stdbool.h>


typedef struct {
    size_t size;
    char *str;
} string;

string make_empty_string(void);
string make_string(char *s);

bool str_isempty(string s);
size_t str_length(string s);
char str_ref(string s, int n);
void print_string(string s);

string concat_string(string s1, string s2);

void destroy_string(string s);

