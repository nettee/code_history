#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include "defs.h"
#include "uslist.h"

typedef struct node_ {
    int val;
    struct node_ *next;
} node;

typedef struct head_ {
    int length;
    node *body;
} head;

typedef head *list;

static node *make_node(int val)
{
    node *pnode = (node *)malloc(sizeof(node));
    if (pnode == NULL)
        return NULL;
    pnode->val = val;
    pnode->next = NULL;
    return pnode;
}

static void free_node(node *pnode)
{
    free(pnode);
}

list make_nil(void)
{
    head *phead = (head *)malloc(sizeof(head));
    phead->length = 0;
    phead->body = NULL;
    return phead;
}

list arr2list(int *arr, int len)
{
    if (len < 0) {
        fprintf(stderr, "arr2list: negative index.\n");
        exit(EXIT_WRONG_ARG);
    }
    list ls = make_nil();
    ls->length = len;
    if (len == 0)
        return ls;
    ls->body = make_node(arr[0]);
    node *q = ls->body;
    for (int i = 1; i < len; i++) {
        node *pnew = make_node(arr[i]);
        q->next = pnew;
        q = q->next;
    }
    return ls;
}

list range(int a, int b)
{
    list ls = make_nil();
    if (a >= b)
        return ls;
    ls->length = b - a;
    ls->body = make_node(a);
    node *q = ls->body;
    for (int i = a+1; i < b; i++) {
        node *pnew = make_node(i);
        q->next = pnew;
        q = q->next;
    }
    return ls;
}

list srange(int a, int b, int step)
{
    list ls = make_nil();
    if (a >= b)
        return ls;
    ls->length = b - a;
    ls->body = make_node(a);
    node *q = ls->body;
    for (int i = a + step; i < b; i++) {
        node *pnew = make_node(i);
        q->next = pnew;
        q = q->next;
    }
    return ls;
}

bool isnull(const list p)
{
    return p->length == 0;
}

int list_length(const list p)
{
    return p->length;
}

int list_offset(const list p, int i)
{
    if (i >= p->length) {
        fprintf(stderr, "list_offset: index out of range.\n");
        exit(EXIT_OUT_OF_RANGE);
    }
    node *q = p->body;
    for (int j = 0; j < i; j++)
        q = q->next;
    return q->val;
}


void represent(const list p)
{
    if (isnull(p))
        puts("[]");
    putchar('[');
    for (node *q = p->body; q!= NULL; q = q->next)
        printf("%d%s", q->val, (q->next != NULL) ? ", " : "]\n");
}
        

