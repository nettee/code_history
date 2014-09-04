#include <stdio.h>

/* all string.h-like functions appeared in the book */

/* pp.29 copy() */
void copy(char to[], char from[])
{
    int i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}

/* pp.31 exercise: reverse() */

/* pp.39 strlen() */
int strlen(char s[])
{
    int i = 0;
    while (s[i] != '\0')
        ++i;
    return i;
}

/* pp.47 squeeze() */
void squeeze(char s[], int c)
{
    int i, j;
    for (i = j = 0; s[i] != '\0'; i++) {
        if (s[i] != c) {
            s[j++] = s[i];
        }
    }
    s[j] = '\0';
}

/* pp.48 strcat() */
void strcat(char s[], char t[])
{
    int i = 0, j = 0;
    while (s[i] != '\0')
        i++;
    while ((s[i++] = t[j++]) != '\0')
        ;
}

/* pp.48 exercise 2-4 squeeze() */

/* pp.48 exercise 2-5 any() */

/* pp.61 atoi() */
int atoi(char s[])
{
    int sign, n;
    for (int i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (n = 0; isdigit(s[i]); i++)
        n = 10 * n + (s[i] - '0');
    return sign * n;
}

/* pp.62 reverse() */
void reverse(char s[])
{
    int c;
    int i = 0;
    int j = strlen(s) - 1;
    for (; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* pp.63 exercise 3-3 expand() */

/* pp.65 trim() */
int trim(char s[])
{
    int n = strlen(s) - 1;
    for (; n >= 0; n--) {
        if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n') {
            break;
        }
    }
    s[n+1] = '\0';
    return n;
}

/* pp.69 strindex() */
int strindex(char s[], char t[])
{
    int i, j, k;
    for (i = 0; s[i] != '\0'; i++) {
        for (j = 1, k = 0; t[k] != '\0' && s[j] == t[k]; 
                j++, k++) 
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}   

/* pp.71 exercise 4-1 strrindex() */

/* pp.88 exercise 4-13 reverse() */

/* pp.99 strlen() */
int strlen(char *s)
{
    int n;
    for (n = 0; *s != '\0'; s++)
        n++;
    return n;
}

/* pp.103 strlen() */
int strlen(char *s)
{
    char *p = s;
    while (*p != '\0')
        p++;
    return p - s;
}

/* pp.105 strcpy()
 *        strcpy()
 *        strcpy()
 */
void strcpy(char *s, char *t)
{
    int i = 0;
    while ((s[i] = t[i]) != '\0')
        i++;
}

void strcpy(char *s, char *t)
{
    while ((*s = *t) != '\0') {
        s++;
        t++;
    }
}

void strcpy(char *s, char *t)
{
    while ((*s++ = *t++) != '\0')
        ;
}

void strcpy(char *s, char *t)
{
    while (*s++ = *t++)
        ;
}

/* pp.106 strcmp() */

/* pp.107 exercise 5-3 5-4 5-5 */
