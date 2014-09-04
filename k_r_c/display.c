#include <stdio.h>

void putint(int n)
{
    printf("%d\n", n);
}

void putstr(const char *s)
{
    while (*s != '\0') {
        putchar(*s);
        s++;
    }
    putchar('\n');
}

void putintarray(const int *list, int N)
{
    for (int i = 0; i < N; i++) {
        printf("%d", list[i]);
        if (i < N - 1) {
            putchar(' ');
        }
    }
    putchar('\n');
}
            
