#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void rearrange(int *v, int len);

int main()
{
    int size;
    int i;
    scanf("%d", &size);
    int *v = (int *)malloc(size * sizeof(int));
    for (i = 0; i < size; i++) {
        scanf("%d", v + i);
    }
    
    rearrange(v, size);
    for (i = 0; i < size; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");

}

void rearrange(int *v, int len)
{
    assert(v);
    assert(len > 0);
    int *left = v;
    int *right = v + len - 1;
    while (left < right) {
        if (*left & 1) {  /* odd */
            ++left;
            continue;
        } else if (!(*right & 1)) {  /* even */
            --right;
            continue;
        } else {
            int t;
            t = *left;
            *left = *right;
            *right = t;
            ++left;
            --right;
        }
    }
}
