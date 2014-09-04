#include <stdio.h>
#include <ctype.h>

int is_alpha(char c)
{
    if (c >= 'A' && c <= 'Z') {
        return 1;
    }
    if (c >= 'a' && c <= 'z') {
        return 1;
    }
    return 0;
}

int is_digit(char c)
{
    if (c >= '0' && c <= '9') {
        return 1;
    } else {
        return 0;
    }
}

int is_lower(char c)
{
    if (c >= 'a' && c <= 'z') {
        return 1;
    } else {
        return 0;
    }
}

int is_upper(char c)
{
    if (c >= 'A' && c <= 'Z') {
        return 1;
    } else {
        return 0;
    }
}

int to_lower(char c)
{
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 'a';
    } else {
        return c;
    }
}

int to_upper(char c)
{
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 'A';
    } else {
        return c;
    }
}

int atoi(char *s)
{
    int n = 0;
    for (char *t = s; isdigit(*t); ++t) {
        n = 10 * n + (*t - '0');
    }
    return n;
}

int ishex(char c)
{
    if (isdigit(c)) {
        return 1;
    } else if (c >= 'a' && c <= 'f') {
        return 1;
    } else if (c >= 'A' && c <= 'F') {
        return 1;
    } else {
        return 0;
    }
}

int hctoi(char c)
{
    if (isdigit(c)) {
        return c - '0';
    } else if (c >= 'a' && c <= 'f') {
        return c - 'a';
    } else if (c >= 'A' && c <= 'F') {
        return c - 'A';
    }
}

int ihtoi(char *s)
{
    int n = 0;
    for (char *t = s; ishex(*t); ++t) {
        n = 16 * n + hctoi(*t);
    }
    return n;
}



long character_count()
{
    long nc = 0;

    while (getchar() != EOF) {
        nc++;
    }
    return nc;
}

long line_count()
{
    char c;
    long nl = 0;

    while((c = getchar()) != EOF) {
        if (c == '\n') {
            nl++;
        }
    }

    return nl;
}

long blank_count()
{
    long nb = 0;
    char c;
    
    while((c = getchar()) != EOF) {
        if (c == ' ') {
            nb++;
        }
    }
    return nb;
}

void rm_unneeded_blank()
{
    /* replace more and one blanks 
     * by a single blank */
    char c;
    char lastc = '0';

    while ((c = getchar()) != EOF) {
        if (!(lastc == ' ' && c == ' ')) {
            putchar(c);
        }
        lastc = c;
    }
}
