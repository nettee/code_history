#include <iostream>
#include "bintree.h"

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
    BinTree<char> t;
    t.input(v, LEN);
    t.preorder_traversal();
    t.inorder_traversal();
    t.postorder_traversal();
    cout << "Longest path in tree has length " << t.max_path_length() << endl;
    return 0;
}
