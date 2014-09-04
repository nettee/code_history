#include <stdio.h>
#include <stdbool.h>
#include "defs.h"

#ifndef II_USLIST_H
#define II_USLIST_H

struct head_;
typedef struct head_ *list;

/* generate or initialize a list */
list make_nil(void);
list arr2list(int *arr, int len);
list range(int a, int b);
list srange(int a, int b, int step);

/* list referrence and show */
bool isnull(const list);
int list_length(const list);
int list_offset(const list, int);
void represent(const list);

/* modify a list */
void list_insert(list, int val);
void list_insertn(list, int index, int val);
void list_append(list, int val);
int list_pop(list);
int list_popn(list, int index);
void list_extend(list, const list);

/* high-level operations */
list list_copy(const list);
list concat_list(const list, const list);
void traverse(void (*pf)(int), const list);
void imap(int (*pf)(int), list);
list map(int (*pf)(int), const list);
void ifilter(bool (*pf)(int), list);
list filter(bool (*pf)(int), const list);
int reduce(int (*pf)(int, int), const list);
int accumulate(int (*pf)(int, int), int initial, const list);

void delete_list(list);

#endif /* II_USLIST_H */
