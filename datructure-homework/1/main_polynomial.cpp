#include "polynomial.h"
#include <iostream>

using namespace std;

int main()
{
    Polynomial p;
    p.input();
    p.output();

    Polynomial q;
    q.input();
    q.output();

    Polynomial s;
    add_poly(p, q, s);
    s.output();
}
