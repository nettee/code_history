#include <stdio.h>
#include <stdbool.h>
#include "defs.h"

#ifndef II_SLLIST_H
#define II_SLLIST_H

struct node_;
typedef struct node_ node;
typedef node *link;
typedef node *list;

/* Node operations. Should not be used by costomer. */
static node *make_node(int);
static void free_node(node *);
static node *copy_node(node *);
static void insert_node(list *, node *);
static void append_node(list *, node *);
static node *search_node(const list p, int val);
static void remove_node(list *, node *);

/* generate or initialize a list */
list make_nil(void);
list make_list(int len, ...);
list arr2list(int *arr, int len);
list range(int a, int b);
list srange(int a, int b, int step);

/* list referrence and show */
bool isnull(const list p);
int len(const list p);
int list_offset(const list p, int i);
void represent(const list p);

/* modify a list */
void list_insert(list *, int val);
void list_insertn(list *, int index, int val);
void list_append(list *, int val);
int list_pop(list *);
int list_popn(list *, int index);
void list_extend(list *, const list *);

/* item operations in a list */
int list_item_count(const list p, int val);
int list_item_index(const list p, int val);
void list_item_remove(list *, int val);
void list_item_purge(list *, int val);

/* high-level operations */
list list_copy(const list p);
list concat_list(const list p1, const list p2);
void traverse(void (*pf)(int), list p);
void imap(int (*pf)(int), list p);
list map(int (*pf)(int), const list p);
list filter(bool (*pf)(int), const list p);
int reduce(int (*pf)(int, int), const list p);
int accumulate(int (*pf)(int, int), int initial, const list);

void delete_list(list *);

#endif   /* II_SLLIST_H */
