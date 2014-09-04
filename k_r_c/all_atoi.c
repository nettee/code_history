#include <stdio.h>

/* all atoi-like functions appeared in the book */

/* pp.43 atoi() */
int atoi(char s[])
{
    int n = 0;
    for (int i = 0; isdigit(s[i]); ++i)
        n = 10 * n + (s[i] - '0');
    return n;
}

/* pp.46 exercise 2-3 htoi() */

/* pp.64 itoa() */
void itoa(int n, char s[])
{
    int i, sign;
    if ((sign = n) < 0) 
        n = -n;
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

/* pp.64 exercise 3-5 itob()
 *       exercise 3-6 itoa() */

/* pp.71 atof() */
double atof(char s[])
{
    double val, power;
    int i, sign;
    for (i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
    }
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    return sign * val / power;
}

/* pp.73 exercise 4-2 atof() */

