#include <stdio.h>
#include <stdbool.h>

char stack[512];

/* stack[top] refer to the first unused place in stack */
int top = 0;

void push(char c)
{
    stack[top++] = c;
}

char pop(void)
{
    return stack[--top];
}

bool is_empty(void)
{
    return top == 0;
}

int main()
{
    push('a');
    push('w');
    push('k');

    while (!is_empty())
        putchar(pop());
    putchar('\n');

    return 0;
}
