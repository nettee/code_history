#include <iostream>
#include <cstdlib>
#include <cassert>

using namespace std;


void output(int *v, int r)
{
    for (int i = 0; i < r; i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

void comb(int *v, int n, int r, int k)
{
    int begin = (k == 0) ? 1 : v[k-1] + 1;
    for (int i = begin; i <= n; i++) {
        v[k] = i;
        if (k == r - 1) { // the last number finished
            output(v, r);
        } else {
            comb(v, n, r, k+1);
        }
    }
    return;
}

void combination(int *v, int n, int r)
{
    comb(v, n, r, 0);
}

int main(int argc, char *argv[])
{
    assert(argc == 3);
    int n = atoi(argv[1]);
    int r = atoi(argv[2]);
    int *v = new int[r];
    combination(v, n, r);

    
    return 0;
}
