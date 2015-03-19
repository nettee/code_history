#include <iostream>
#include <cassert>
#include "stack.h"

using namespace std;

void input(int *v, int n)
{
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
}

void output(int *v, int n)
{
    for (int i = 0; i < n; i++) {
        cout << v[i] << " ";
    } 
    cout << endl;
}

bool pop_seq(int *vpush, int *vpop, int n)
{
    Stack<int> s;
    int i = 0, j = 0;

    while(j < n) {
        if (!s.empty() && s.top() == vpop[j]) {
            s.pop();
            j++;
        } else {
            if (i == n) return false; 
            s.push(vpush[i]);
            i++;
        }
    }
    return true;
}

int main() 
{
    int n;
    cin >> n;
    int *vpush, *vpop;
    vpush = new int[n];
    vpop = new int[n];
    input(vpush, n);
    input(vpop, n);
    cout << "Push sequence: ";
    output(vpush, n);
    cout << "Pop sequence: ";
    output(vpop, n);

    if(pop_seq(vpush, vpop, n)) {
        cout << "Good pop sequence." << endl;
    } else {
        cout << "Bad pop sequence." << endl;
    }
    delete[] vpush;
    delete[] vpop;
    return 0;
}
