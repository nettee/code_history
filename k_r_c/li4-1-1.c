#include <stdio.h>
#define MAXLINE 1000

// successfully compiled, but wrong result got
// study again next time
// note:
// switch '-std=c89' when compiling

int getline(char line[], int max);
int strindex(char source[], char searchfor[]);

char pattern[] = "ould";

int main(void)
{
    char line[MAXLINE];
    int found = 0;
    
    while(getline(line, MAXLINE)){
        if(strindex(line, pattern) >= 0){
            printf("%s", line);
            found++;
        }
    }
    return found;
}

int getline(char s[], int lim)
{
    int c;
    int i = 0;
    while(--lim > 0 && (c = getchar()) != EOF && c != '\n'){
        s[i++] = c;
    }
    if(c == '\n'){
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}

int strindex(char s[], char t[]){
    int i, j, k;

    for(i = 0; s[i] != '\0'; i++){
        for(j = 1, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++){
            ;
        }
        if(k > 0 && t[k] == '\0'){
            return i;
        }
    }
    return -1;
}

