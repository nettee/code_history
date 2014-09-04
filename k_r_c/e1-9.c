#include <stdio.h>

/*copy the input to output, replacing each string of one or more blanks
 * by a single blank */

int main(void)
{
    char c;
    char lastc = '0';

    while ((c = getchar()) != EOF) {
        if (!(lastc == ' ' && c == ' ')) {
            putchar(c);
        }
        lastc = c;
    }
    return 0;
}
