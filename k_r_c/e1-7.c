#include <stdio.h>

/*copy the input to output, replacing each string of one or more blanks
 * by a single blank */

int main(void)
{
    puts("in 1-9");


    int c_is_blank = 0;
    int c;

    while((c = getchar()) != EOF){
        if(c_is_blank){
            if(c != ' '){
                putchar(c);
                c_is_blank = 0;
            }
        } else {
            putchar(c);
        }
    }
    return 0;

}
