#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>

#ifndef _POLYNOMIAL_H_
#define _POLYNOMIAL_H_

struct term {
    double coeff;
    int expo;
    term *next;
    term(double c, int e) {
        coeff = c;
        expo = e;
        next = NULL;
    }
};

class Polynomial {
public:
    Polynomial();
    Polynomial(Polynomial& p);
    ~Polynomial();

    bool empty();
    int length();

    void push_front(double c, int e);
    void pop_front();
    void push_back(double c, int e);

    term *gethead() { return head; }

    void input();
    void output();

private:
    term *head;
    term *last;
    int size;
};


Polynomial::Polynomial()
{
    head = new term(0.0, -1);
    head->next = head;
    last = head;
    size = 0;
}

Polynomial::Polynomial(Polynomial& L)
{
    head = new term(0.0, -1);
    size = L.length();
    term *p = L.head;
    term *q = head;
    for (int i = 0; i < size; i++) {
        p = p->next;
        term *np = new term(p->coeff, p->expo);
        q->next = np;
        q = q->next;
        if (i == size - 1) {  // last term
            last = q;
            q->next = head;
        }
    }
}

Polynomial::~Polynomial()
{
    for (int i = 0; i < size; i++) {
        pop_front();
    }
}

bool Polynomial::empty()
{
    return size == 0;
}

int Polynomial::length()
{
    return size;
}

void Polynomial::push_front(double c, int e)
{
    term *q = new term(c, e);
    if (size == 0) {
        last = q;
    }
    q->next = head->next;
    head->next = q;
    ++size;
}

void Polynomial::pop_front()
{
    assert(size != 0);
    term *q = head->next;
    head->next = q->next;
    delete q;
    --size;
    if (size == 0) {
        last = head;
    }
}

void Polynomial::push_back(double c, int e)
{
    term *q = new term(c, e);
    q->next = head;
    // note that in empty list, var last is head
    last->next = q;
    last = q;
    ++size;
}

void Polynomial::input()
{
    double c;
    int e;
    while (true) {
        std::cin >> c >> e;
        if (e == -1)
            return;
        push_back(c, e);
    }
}

void Polynomial::output()
{
    term *q = head->next;
    for (int i = 0; i != size; ++i) {
        std::cout << "(" << q->coeff << ", ";
        std::cout << q->expo << ") ";
        q = q->next;
    }
    std::cout << std::endl;
}

// add polynomial a and b, put result in c
// c must be empty
// usage:
//      Polynomial a;
//      a.input();
//      Polynomial b;
//      b.input();
//      Polynomial c;
//      add_poly(a, b, c);
//
void add_poly(Polynomial& a, Polynomial& b, Polynomial& c)
{
    assert(c.empty());
    term *pa = a.gethead()->next;
    term *pb = b.gethead()->next;
    while (pa != a.gethead() || pb != b.gethead()) {
        if (pa == a.gethead()) {
            c.push_back(pb->coeff, pb->expo);
            pb = pb->next;
        } else if (pb == b.gethead()) {
            c.push_back(pa->coeff, pa->expo);
            pa = pa->next;
        } else if (pa->expo > pb->expo) {
            c.push_back(pb->coeff, pb->expo);
            pb = pb->next;
        } else if (pa->expo < pb->expo) {
            c.push_back(pa->coeff, pa->expo);
            pa = pa->next;
        } else {
            double t = pa->coeff + pb->coeff;
            if (fabs(t) > 0.001) {
                c.push_back(t, pa->expo);
            }
            pa = pa->next;
            pb = pb->next;
        }
    }
}

#endif
