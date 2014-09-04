#include <stdio.h>
#include "istring.h"

size_t istrlen(const char *s)
{
    size_t len = 0;
    for ( ; *s != '\0'; s++)
        ++len;
    return len;
}

char *istrcpy(char *dest, const char *src)
{
    char *s = dest;
    while ((*s++ = *src++))
        ;
    return dest;
}

char *istrncpy(char *dest, const char *src, size_t n)
{
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];
    for ( ; i < n; i++)
        dest[i] = '\0';
    return dest;
}

char *istrcat(char *dest, const char *src)
{
    char *s = dest;
    while (*s != '\0')
        s++;
    while ((*s++ = *src++))
        ;
    *s = '\0';
    return dest;
}

char *istrncat(char *dest, const char *src, size_t n)
{
    char *s = dest;
    while (*s != '\0')
        s++;
    while ((*s++ = *src++) && n-- > 0)
        ;
    *s = '\0';
    return dest;
}

int istrcmp(const char *s1, const char *s2)
{
    for( ; *s1 == *s2; s1++, s2++) {
        if (*s1 == '\0')
            return 0;
    }
    return *s1 - *s2;
}

int istrncmp(const char *s1, const char *s2, size_t n)
{
    for ( ; n-- > 0; s1++, s2++)
        if (*s1 != *s2)
            return *s1 - *s2;
    return 0;
}

