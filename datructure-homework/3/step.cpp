#include <iostream>

using namespace std;

int step_recr(int n)
{
    if (n <= 1) {
        return 1;
    } else {
        return step_recr(n-1) + step_recr(n-2);
    }
}

int step(int n) 
{
    if (n <= 1) {
        return 1;
    }
    int *steps = new int[n+1];
    steps[0] = 1;
    steps[1] = 1;
    for (int i = 2; i <= n; i++) {
        steps[i] = steps[i-1] + steps[i-2];
    }
    return steps[n];
}

int main()
{
    int n;
    cin >> n;
    cout << step(n) << endl;
    cout << step_recr(n) << endl;
    return 0;
}
