#include <stdio.h>

int getline(char s[], int lim)
{
    char c;
    int i = 0, j = 0;
    while((c = getchar()) != EOF && c != '\n') {
        if (i < lim - 2) {
            s[j] = c;
            ++j;
        }
        i++;
    }
    s[j] = c;
    ++i;
    ++j;
    s[j] = '\0';
    return i;
}
