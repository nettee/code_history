#include "avltree.h"

#include <iostream>
#include <cassert>

int arr[] = {
    3, 2, 1, 4, 5, 6, 7,
    16, 15, 14, 13, 12, 11, 10, 8, 9,
};

#define ARRAY_SIZE ((sizeof arr) / (sizeof arr[0]))

using namespace std;

int main()
{
    AvlTree<int> t;
    t.fromArray(arr, ARRAY_SIZE);
    cout << " preorder: ";
    t.preorder();
    cout << "  inorder: ";
    t.inorder();
    cout << "postorder: ";
    t.postorder();
    return 0;
}
