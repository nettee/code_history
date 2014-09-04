#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include "defs.h"
#include "sllist.h"

typedef struct node_ {
    int val;
    struct node_ *next;
} node;

typedef node *list;

static node *make_node(int val)
{
    node *pnode = (node *)malloc(sizeof(node));
    if (pnode == NULL)
        return NULL;
    pnode->val = val;
    pnode->next = NULL;
    return pnode;
}

static void free_node(node *p)
{
    free(p);
}

list make_nil(void)
{
    return NULL;
}

list make_list(int len, ...)
{
    list ls = make_nil();
    va_list ip;
    int ival;
    va_start(ip, len);
    for (int i = 0; i < len; i++) {
        ival = va_arg(ip, int);
        list_append(&ls, ival);
    }
    va_end(ip);
    return ls;
}

list arr2list(int *arr, int len)
{
    list ls = make_nil();
    for (int i = 0; i < len; i++)
        list_append(&ls, arr[i]);
    return ls;
}

list range(int a, int b)
{
    list ls = make_nil();
    for (int i = a; i < b; i++)
        list_append(&ls, i);
    return ls;
}

list srange(int a, int b, int step)
{
    list ls = make_nil();
    for (int m = a; m < b; m += step)
        list_append(&ls, m);
    return ls;
}

bool isnull(const list p)
{
    return p == NULL;
}

int len(const list p)
{
    int count = 0;
    for (node *q = p; q != NULL; q = q->next)
        ++count;
    return count;
}

int list_offset(const list p, int i)
{
    if (isnull(p)) {
        fprintf(stderr, "list_offset: index out of range.\n");
        exit(EXIT_OUT_OF_RANGE);
    }
    node *q = p;
    for (int j = 0; j < i; j++) {
        q = q->next;
        if (q == NULL) {
            fprintf(stderr, "list_offset: index out of range.\n");
            exit(EXIT_OUT_OF_RANGE);
        }
    }
    return q->val;
}

void represent(const list p)
{
    if (isnull(p))
        puts("[]");
    putchar('[');
    for (node *q = p; q != NULL; q = q->next)
        printf("%d%s", q->val, (q->next == NULL) ? "]\n" : ", ");
}

void list_insert(list *pp, int val)
{
    node *pnew = make_node(val);
    if (pnew == NULL) {
        fprintf(stderr, "insert error: node do not exist.\n");
        exit(EXIT_NO_OBJECT);
    }
    pnew->next = *pp;
    *pp = pnew;
}

void list_append(list *pp, int val)
{
    node *pnew = make_node(val);
    if (pnew == NULL) {
        fprintf(stderr, "append error: node do not exist.\n");
        exit(EXIT_NO_OBJECT);
    }
    if (isnull(*pp)) {
        *pp = pnew;
    } else {
        node *q = *pp;
        while (q->next != NULL)
            q = q->next;
        q->next = pnew;
    }
}

int list_pop(list *pp)
{
    if (isnull(*pp)) {
        fprintf(stderr, "pop error: pop from empty list.\n");
        exit(EXIT_OUT_OF_RANGE);
    }
    node **qq = pp;
    while ((*qq)->next != NULL) 
        qq = &(*qq)->next;
    int result = (*qq)->val;
    free_node(*qq);
    *qq = NULL;
    return result;
}
    
int list_popn(list *pp, int index)
{
    if (isnull(*pp)) {
        fprintf(stderr, "popn: index out of range");
        exit(EXIT_OUT_OF_RANGE);
    }
    node **qq = pp;
    for (int j = 0; j < index; j++) {
        qq = &(*qq)->next;
        if ((*qq) == NULL) {
            fprintf(stderr, "popn: index out of range.\n");
            exit(EXIT_OUT_OF_RANGE);
        }
    }
    int result = (*qq)->val;
    node *t = *qq;
    free_node(t);
    *qq = (*qq)->next;
    return result;   
}

void list_extend(list *pp1, const list *pp2)
{
    if (isnull(*pp1))
        *pp1 = *pp2;
    node *q = *pp1;
    while (q->next != NULL)
        q = q->next;
    q->next = *pp2;
} 

int list_item_count(const list p, int val)
{
    int count = 0;
    for (node *q = p; q != NULL; q = q->next)
        if (q->val == val)
            ++count;
    return count;
}

int list_item_index(const list p, int val)
{
    int index = 0;
    for (node *q = p; q != NULL; q = q->next) {
        if (q->val == val)
            return index;
        ++index;
    }
    fprintf(stderr, "index: item cannot find.\n");
    exit(EXIT_WRONG_ANS);
}

void list_item_remove(list *pp, int val)
{
    node *q;
    while ((q = *pp) != NULL) {
        if (q->val == val) {
            *pp = q->next;
            free_node(q);
            return;
        }
        pp = &q->next;
    }
    fprintf(stderr, "remove: item cannot find.\n");
    exit(EXIT_WRONG_ANS);
}

void list_item_purge(list *pp, int val)
{
    node *q;
    while ((q = *pp) != NULL) {
        if (q->val == val) {
            *pp = q->next;
            free_node(q);
        }
        pp = &q->next;
    }
}

list list_copy(const list p)
{
    list ls = make_nil();
    for (node *q = p; q != NULL; q = q->next) {
        list_append(&ls, q->val);
    }
    return ls;
}

list concat_list(const list p1, const list p2)
{
    list ls = list_copy(p1);
    list_extend(&ls, &p2);
    return ls;
}

void traverse(void (*pf)(int), list p)
{
    for (node *q = p; q != NULL; q = q->next)
        (*pf)(q->val);
}

void imap(int (*pf)(int), list p)
{
    for (node *q = p; q != NULL; q = q->next)
        q->val = (*pf)(q->val);
}

list map(int (*pf)(int), const list p)
{
    list ls = make_nil();
    for (node *q = p; q != NULL; q = q->next) {
        list_append(&ls, (*pf)(q->val));
    }
    return ls;
}

list filter(bool (*pf)(int), const list p)
{
    list ls = make_nil();
    for (node *q = p; q != NULL; q = q->next) {
        if ((*pf)(q->val))
            list_append(&ls, q->val);
    }
    return ls;
}

int reduce(int (*pf)(int, int), const list p)
{
    if (isnull(p)) {
        fprintf(stderr, "reduce() of empty list.\n");
        exit(EXIT_WRONG_ARG);
    }
    int result = p->val;
    for (node *q = p->next; q != NULL; q = q->next)
        result = (*pf)(result, q->val);
    return result;
}

int accumulate(int (*pf)(int, int), int initial, const list p)
{
    int result = initial;
    for (node *q = p; q != NULL; q = q->next)
        result = (*pf)(result, q->val);
    return result;
}

void delete_list(list *pp)
{
    node *p = *pp;
    node *q;
    while (p != NULL) {
        q = p->next;
        free_node(p);
        p = q;
    }
}
