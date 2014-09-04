#include <stdio.h>
#include "stream.h"

#define MAXLINE 100


void rclean(char *line);
int is_blank_line(char *line);

/* error
 *
 *
 * appears
 *
 *
 *
 *
 */


int main()
{
    char line[MAXLINE];
    for(int i = 0; i < MAXLINE; i++){
        line[i] = '\0';
    }

    while(getline(line, MAXLINE)){
        if (is_blank_line(line)) {
            break;
        } else {
            rclean(line);
            printf("%s", line);
        }
    }
    
    return 0;
}

int is_blank_line(char *line)
{
    if (line[0] == '\n' && line[1] == '\0') {
        return 1;
    } else {
        return 0;
    }
}

void rclean(char *line)
{
    char *t = line;
    while(*t) {
        t++;
    } // find end of string
    t--;  
    while(*t == ' ' || *t == '\t'){
        *t = '\0';
        t--;
    }
}
