#include <iostream>
#include "bintree.h"

using namespace std;

int v1[29] = {
                   40,
           18,             56,
       12,     0,      45,     62,
     8,  16, 0,  0,  0,  50, 60,  0,
    0,0,0,0,0,0,0,0,0,0,0,0,59,61,
};

int v2[29] = {
                   40,
           18,             56,
       12,     0,      45,     62,
     8,  16, 0,  0,  0,  57, 60,  0,
    0,0,0,0,0,0,0,0,0,0,0,0,59,61,
};

int main()
{
    BinTree<int> t1;
    t1.input(v1, 29);
    t1.inorder_traversal();

    BinTree<int> t2;
    t2.input(v2, 29);
    t2.inorder_traversal();

    return 0;
}
