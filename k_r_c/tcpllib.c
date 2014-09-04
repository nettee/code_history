#include <stdio.h>

long power(int base, int n);
int getline(char s[], int lim);

long power(int base, int n)
{
    long pow = 1;
    for(int i = 0; i < n; i++){
        pow *= base;
    }
    return pow;
}

int old_getline(char s[], int lim)
{
    int c, i;
    for(int i = 0; i < lim - 1 && (c=getchar()) != EOF && c != '\n'; i++){
        s[i] = c;
    }
    if(c == '\n'){
        s[i] = c;   //此处出现严重段错误!
        i++;
    }
    s[i] = '\0';
    return i;
}

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
    s[j] = '\n';
    s[j+1] = '\0';
    return i+1;
}

void copy(char to[], char from[])
{
    int i = 0;
    while ((to[i] = from[i]) != '\0') {
        i++;
    }
}

int main()
{
    char s[100];
    getline(s, 100);
    printf("%s", s);
    return 0;
}

