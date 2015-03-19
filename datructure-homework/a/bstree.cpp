#include "bstree.h"

#include <iostream>
#include <cassert>

using namespace std;

int main()
{
    int arr[15] = {4, 11, 9, 1, 5, 6, 8, 2, 12, 3, 14, 15, 7, 10, 13};
    BinSearchTree<int> t;
    t.fromArray(arr, 15);
    t.toArray(arr, 15);
    for (int i = 0; i < 15; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}
