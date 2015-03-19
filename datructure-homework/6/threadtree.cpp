#include <iostream>
#include "threadtree.h"

using namespace std;

char v[] = {
                                  'A',


                  'B',                            'C',

          'D',            '*',            'E',            'F',

      'G',    'H',    '*',    '*',    '*',    'I',    'J',   '*',
    '*','*','*','*','*','*','*','*','*','*','*','K','L','M',
};
#define LEN (sizeof(v) / sizeof(v[0]))

int main()
{
    ThreadTree<char> t;
    t.input(v, LEN);
    t.preorder_traversal();
    t.inorder_traversal();
    t.postorder_traversal();
    t.pre_thread();
    t.pre_order();
    return 0;
}
