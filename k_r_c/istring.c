#include <stdio.h>

void escape(char *s, char *t)
{
    while (*t) {
        if (*t == '\\') {
            ++t;
            switch (*t) {
            case 'n':
                *s++ = '\n';
                break;
            case 't':
                *s++ = '\t';
                break;
            default:
                *s++ = '\\';
                *s++ = *t;
                break;
            }
            ++t;
        } else {
            *s++ = *t++;
        }
    }
    *s = '\0';
}

void istrcpy(char *s, char *t)
{
    while (*s++ = *t++)
        ;
}

int istrcmp(char *s, char *t)
{
    for( ; *s == *t; s++, t++) {
        if (*s == '\0')
            return 0;
    }
    return *s - *t;
}
