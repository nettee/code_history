#include <stdio.h>

/* quite robust program */

void expand(const char *src, char *dest)
{
    int i = 0, j = 0;
    while (src[i] != '\0') {
        if (i == 0) {
            dest[j++] = src[i++];
            continue;
        } 
        
        
        if (src[i] == '-' && src[i+1] != '\0') {
            char start = src[i-1];
            char end = src[i+1];
            if (start < end)
                for (char c = start+1; c <= end; c++)
                    dest[j++] = c;
            else
                for (char c = start-1; c >= end; c--)
                    dest[j++] = c;
                
            i += 2;
        } else {
            dest[j++] = src[i++];
        }
    }
    dest[j] = '\0';
}

int main(void)
{
    char src[] = "!-z";
    char dest[100];
    expand(src, dest);
    
    puts(dest);
}

