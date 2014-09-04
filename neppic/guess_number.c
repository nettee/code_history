#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int game(int ubound);
int match_position(int *target, int *current);
int match_num(int *target, int *current);
int sample(int *list, int N);
int print_array(const int *list, int N);

void sample(int *list, int N)
{   // NOT COMPLETED!!!
    list[0] = 1;
    list[1] = 2;
    list[2] = 3;
    list[3] = 4;
}
    

void print_array(const int *list, int N)
{
    int i;
    putchar('[');
    for(i = 0; i < N; i++){
        printf("%d", list[i]);
        if(i < N - 1){
            putchar(',');
            putchar(' ');
        }
    }
    putchar(']');
    putchar('\n');
}

int match_num(int *target, int *current){
    int i = 0, j = 0;
    int nc = 0;
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            if (current[i] == target[j]){
                nc++;
                break;
            }
        }
    }
    return nc;
}

int match_position(int *target, int *current){
    int i = 0;
    int pc = 0;
    for (i = 0; i < 4; i++){
        if (target[i] == current[i]){
            pc++;
        }
    }
    return pc;
}

int game(int ubound)
{
    int target[4];
    int round;
    int nums[4];   // answer from user

    sample(target, 4);
    
    for(round = 1; round < 10; round++){
        printf("Enter 4 numbers, splitted by space:");
        scanf("%d%d%d%d", nums, nums+1, nums+2, nums+3);

        int match_n = match_num(target, nums);
        int match_p= match_position(target, nums);

        if(match_n == 4 && match_p == 4){
            printf("Congratulations! You've got the right answer: ");
            print_array(nums, 4);
            return 0;
        } else {
            printf("[round %d]:", round);
            print_array(nums, 4);
            printf("%d correct number(s),", match_n);
            printf(" in which %d number(s) at right position\n", match_p);
        } 
    }
    printf("Game Over! Tries run out.\n");
    return 0;
}


int main()
{
    printf("Guess Number V1.9, Author: William, Sept 2013\n");
    char choice;
    
    /* easy:1~6, normal:1~7, hard:1~9 */
    while(1){
        printf("[e]Easy, [n]Normal, [h]Hard, [q]Quit >>\n");
        scanf("%c", &choice);
        if (choice == 'q'){
            break;
        } else if (choice == 'e'){
            game(6);
        } else if (choice == 'n'){
            game(7);
        } else if (choice == 'h'){
            game(9);
        } else {
            printf("invalid input, try again\n");
        }
    }
    return 0;
}

