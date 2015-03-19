#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>

#ifndef _LSTACK_H_
#define _LSTACK_H_

template <typename T>
struct node{
    T val;
    node *next;
    node(T data) {
        val = data;
        next = NULL;
    }
};

template <typename T>
class lstack {
public:
    lstack();
    ~lstack();

    bool empty()const;
    int size()const;
    
    void push(T x);
    T pop();
    void clear();

    void output();

private:
    node<T> *top;
};

template <typename T>
lstack<T>::lstack()
{
    top = NULL;
}

template <typename T>
lstack<T>::~lstack()
{
    clear();
}

template <typename T>
bool lstack<T>::empty()const
{
    return top == NULL;
}

template <typename T>
int lstack<T>::size()const
{
    int n = 0;
    for (node<T> *q = top; q != NULL; q = q->next) {
        ++n;
    }
    return n;
}

template <typename T>
void lstack<T>::push(T x)
{
    node<T> *q = new node<T>(x);
    q->next = top;
    top = q;
}

template <typename T>
T lstack<T>::pop()
{
    assert(!empty());
    node<T> *q = top;
    top = top->next;
    T x = q->val;
    delete q;
    return x;
}

template <typename T>
void lstack<T>::clear()
{
    while (!empty()) {
        pop();
    }
}

template <typename T>
void lstack<T>::output()
{
    for (node<T> *q = top; q != NULL; q = q->next) {
        std::cout << q->val << " ";
    }
    std::cout << std::endl;
}

#endif
