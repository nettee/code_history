#include <iostream>

#include "disjset.h"

using namespace std;

int main()
{
    DisjointSet s(10);
    int d1, d2;
    while (true) {
        cin >> d1 >> d2;
        if (cin) {
            cout << "(" << d1 << ", " << d2 << ") ";
        } else {
            break;
        }
        s.setUnion(d1, d2);
    }
    cout << endl;
    s.print_disjoint_set();
    return 0;
}
