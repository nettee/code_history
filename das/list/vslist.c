#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include "defs.h"
#include "vslist.h"

#define MAXLEN 100

typedef struct node_ {
    int val;
    struct node_ *next;
} node;

typedef node *link;
typedef node *list;

node *make_node(int val)
{
    node *pnode = (node *) malloc(sizeof(node));
    if (pnode == NULL)
        return NULL;
    pnode->val = val;
    pnode->next = NULL;
    return pnode;
}

void free_node(node *p)
{
    free(p);
}

node *copy_node(node *pnode)
{
    node *pnew = (node *)malloc(sizeof(node));
    if (pnew == NULL)
        return NULL;
    pnew->val = pnode->val;
    pnew->next = NULL;
    return pnew;
}

List insert_node(List p, node *pnode)
{
    if (pnode == NULL) {
        fprintf(stderr, "insert error: node do not exist.\n");
        exit(EXIT_NO_OBJECT);
    }
    pnode->next = p;
    return pnode;
}

List append_node(List p, node *pnode)
{
    if (pnode == NULL) {
        fprintf(stderr, "append error: node do not exist.\n");
        exit(EXIT_NO_OBJECT);
    }
    if (p == NULL) {
        p = pnode;
    } else {
        node *q = p;
        while (q->next != NULL)
            q = q->next;
        q->next = pnode;
    }
    return p;
}

node *search_node(const List p, int val)
{
    for (node *q = p; q != NULL; q = q->next) {
        if (q->val == val)
            return q;
    }
    return NULL;
}

List remove_node(List p, node *pnode)
{
    if (pnode == NULL || isnull(p))
        return p;
    if (pnode == p) {
        p = pnode->next;
        free_node(pnode);
        return p;
    }
    for (node *prev = p; prev->next != NULL; prev = prev->next) {
        if (prev->next == pnode) {
            prev->next = pnode->next;
            free_node(pnode);
        }
    }
    return p;
}            

List make_nil(void)
{
    return NULL;
}

List make_list(int len, ...)
{
    List ls = make_nil();
    va_list ip;
    int ival;
    va_start(ip, len);
    for (int i = 0; i < len; i++) {
        ival = va_arg(ip, int);
        ls = list_append(ls, ival);
    }
    va_end(ip);
    return ls;
}

List arr2list(int *arr, int len)
{
    List ls = make_nil();
    for (int i = 0; i < len; i++)
        ls = list_append(ls, arr[i]);
    return ls;
}

List range(int a, int b)
{
    List ls = make_nil();
    for (int i = a; i < b; i++)
        ls = list_append(ls, i);
    return ls;
}

List srange(int a, int b, int step)
{
    List ls = make_nil();
    for (int m = a; m < b; m += step)
        ls = list_append(ls, m);
    return ls;
}

bool isnull(List p)
{
    return p == NULL;
}

int len(const List p)
{
    int count = 0;
    for (node *q = p; q != NULL; q = q->next)
        ++count;
    return count;
}

int list_offset(const List p, int i)
{
    node *q = p;
    if (q == NULL) {
        fprintf(stderr, "list_offset: index out of range.\n");
        exit(EXIT_OUT_OF_RANGE);
    }
    for (int j = 0; j < i; j++) {
        q = q->next;
        if (q == NULL) {
            fprintf(stderr, "list_offset: index out of range.\n");
            exit(EXIT_OUT_OF_RANGE);
        }
    }
    return q->val;
}

void represent(const List p)
{
    putchar('[');
    for (node *q = p; q != NULL; q = q->next)
        printf("%d%s", q->val, (q->next == NULL) ? "]\n" : ", ");
}

List list_insert(List p, int val)
{
    node *np = make_node(val);
    if (p == NULL) {
        fprintf(stderr, "insert error: node do not exist.\n");
        exit(EXIT_NO_OBJECT);
    }
    np->next = p;
    return np;
}

List list_append(List p, int val)
{
    node *pnew = make_node(val);
    if (pnew == NULL) {
        fprintf(stderr, "append error: node do not exist.\n");
        exit(EXIT_NO_OBJECT);
    }
    if (p == NULL) {
        p = pnew;
    } else {
        node *q = p;
        while (q->next != NULL)
            q = q->next;
        q->next = pnew;
    }
    return p;
}

List list_extend(List ls1, List ls2)
{
    if (isnull(ls1))
        return ls2;
    node *q = ls1;
    while (q->next != NULL)
        q = q->next;
    q->next = ls2;
    return ls1;
} 

int list_item_count(const List p, int val)
{
    int count = 0;
    for (node *q = p; q != NULL; q = q->next)
        if (q->val == val)
            ++count;
    return count;
}

int list_item_index(const List p, int val)
{
    int index = 0;
    for (node *q = p; q != NULL; q = q->next) {
        if (q->val == val)
            return index;
        ++index;
    }
    fprintf(stderr, "index: cannot find item.\n");
    exit(EXIT_WRONG_ANS);
}

List list_item_purge(List p, int val)
{
    /* very smart code, inspired from coolshell.cn */
    node **pp = &p;
    node *q;
    while ((q = *pp) != NULL) {
        if (q->val == val) {
            *pp = q->next;
            free_node(q);
        }
        pp = &q->next;
    }
    return p;
}

List list_copy(const List p)
{
    List ls = make_nil();
    for (node *q = p; q != NULL; q = q->next) {
        node *pnew = copy_node(q);
        ls = append_node(ls, pnew);
    }
    return ls;
}

void traverse(void (*pf)(int), List p)
{
    for (node *q = p; q != NULL; q = q->next)
        (*pf)(q->val);
}

void imap(int (*pf)(int), List p)
{
    for (node *q = p; q != NULL; q = q->next)
        q->val = (*pf)(q->val);
}

List map(int (*pf)(int), const List p)
{
    List ls = make_nil();
    for (node *q = p; q != NULL; q = q->next) {
        ls = list_append(ls, (*pf)(q->val));
    }
    return ls;
}

List filter(bool (*pf)(int), const List p)
{
    List ls = make_nil();
    for (node *q = p; q != NULL; q = q->next) {
        if ((*pf)(q->val))
            ls = list_append(ls, q->val);
    }
    return ls;
}

int reduce(int (*pf)(int, int), const List p)
{
    if (isnull(p)) {
        fprintf(stderr, "reduce() of empty list.\n");
        exit(EXIT_WRONG_ARG);
    }
    node *q = p;
    int result;
    for ( ; q != NULL; q = q->next)
        result = (*pf)(result, q->val);
    return result;
}

int accumulate(int (*pf)(int, int), int initial, const List p)
{
    int result = initial;
    for (node *q = p; q != NULL; q = q->next)
        result = (*pf)(result, q->val);
    return result;
}

void delete_list(List p)
{
    node *q;
    while (p != NULL) {
        q = p->next;
        free_node(p);
        p = q;
    }
}
