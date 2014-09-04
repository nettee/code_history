#include <stdio.h>

#define IN 1
#define OUT 0

/* prints the input one word per line */

int main()
{
    int c;
    int state = IN;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            state = OUT;
        } else if (state == IN) {
            putchar(c);
        } else {
            state = IN;
            putchar('\n');
            putchar(c);
        }
    }
    putchar('\n');
    return 0;
}
