#include <stdio.h>
#include <stdbool.h>
#include "defs.h"

/* 
 * vslist -- very simplest list
 * the first version of linked list ADT,
 * old and without new fixes, hidden bugs may exist
 * not under construction anymore,
 * see the newer sllist, with richer functions
 * 
 *
 * Author: nettee
 * Year: 2014
 */

#ifndef II_VSLIST_H
#define II_VSLIST_H

/* Node operations. Should not be used by costomer. */
node *make_node(int);
void free_node(node *);
node *copy_node(node *);
List insert_node(List p, node *);
List append_node(List p, node *);
node *search_node(const List p, int val);
List remove_node(List p, node *pnode);

/* generate or initialize a list */
List make_nil(void);
List make_list(int len, ...);
List arr2list(int *arr, int len);
List range(int a, int b);
List srange(int a, int b, int step);

/* list referrence and show */
bool isnull(const List p);
int len(const List p);
int list_offset(const List p, int i);
void represent(const List p);

/* modify a list */
List list_insert(List p, int val);
List list_append(List p, int val);
List list_extend(List p, List q);

/* item operations in a list */
int list_item_count(const List p, int val);
int list_item_index(const List p, int val);
List list_item_remove(List p, int val);
List list_item_purge(List p, int val);

/* high-level operations */
List list_copy(const List p);
void traverse(void (*pf)(int), List p);
void imap(int (*pf)(int), List p);
List map(int (*pf)(int), const List p);
List filter(bool (*pf)(int), const List p);
int reduce(int (*pf)(int, int), const List p);
int accumulate(int (*pf)(int, int), int initial, const List);

void delete_list(List p);

#endif   /* II_VSLIST_H */
