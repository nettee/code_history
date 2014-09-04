#include <stdio.h>
#include <stdlib.h>
#include "istring.h"

int main(void)
{
    char *s1 = "hello, world";
    char *s2 = "you silly cunt, hhhhh...";
    char s[100];
    puts("-----strlen---------");
    printf("%u\n", (unsigned)istrlen(s1));
    printf("%u\n", (unsigned)istrlen(s2));
    puts("------strcpy------------");
    istrcpy(s, s2);
    istrcat(s, s1);
    istrcat(s, s1);
    puts(s);
}
