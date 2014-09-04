#include <stdio.h>

int main(void){
    int c;
    int i, j;
    int wlen; 
    int wlc[10];  

    for(i = 0; i < 9; i++){
        wlc[i] = 0;
    }
    
    while ((c = getchar()) != EOF){
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '\''){
            wlen += 1;
        } else {
            if (wlen != 0){
                wlc[wlen-1] += 1;
                wlen = 0;
            } 
        }
    }

    for(i = 0; i < 9; i++){
        printf("%d:   ", i+1);
        for(j = 0; j < wlc[i]; j++){
            printf("-");
        }
        printf("\n");
    }
    printf("+:   ");

    for(j = 0; j < wlc[9]; j++){
        printf("-");
    }
    printf("\n");
    
    return 0;
}
