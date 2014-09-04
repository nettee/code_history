#include <stdio.h>

void escape(char *s, char *t)
{
    while (*t != '\0') {
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
            ++t;
            }
        } else {
            *s++ = *t++;
        }
    }
    *s = '\0';
}

int main(int argc, char *argv[])
{
    
    char s[100];
    escape(s, argv[1]);
    printf("%s", s);
    putchar('\n');
    return 0;
}
