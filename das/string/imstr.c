#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "imstr.h"

string make_empty_string(void)
{
    string new;
    new.size = 0;
    return new;
}

string make_string(char *s)
{
    size_t n = strlen(s);
    string new;
    new.size = n;
    new.str = (char *)malloc(n);

    for (int i = 0; i < n; i++)
        new.str[i] = s[i];
    
    return new;
}

bool str_isempty(string s)
{
    return s.size == 0;
}

size_t str_length(string s)
{
    return s.size;
}

char str_ref(string s, int n)
{
    if (n < 0 || n >= s.size) {
        fprintf(stderr, "string reference out of range.\n");
        exit(EXIT_FAILURE);
    }
    return s.str[n];
}

void print_string(string s)
{
    for (int i = 0; i < s.size; i++)
        putchar(s.str[i]);
    putchar('\n');
}

string concat_string(string s1, string s2)
{
    int n = s1.size + s2.size;
    string s;
    s.size = n;
    s.str = (char *)malloc(n);
    for (int i = 0; i < s1.size; i++)
        s.str[i] = s1.str[i];
    for (int i = 0; i < s2.size; i++)
        s.str[i + s1.size] = s2.str[i];
    return s;
}

void destroy_string(string s)
{
    free(s.str);
    s.size = 0;
}



