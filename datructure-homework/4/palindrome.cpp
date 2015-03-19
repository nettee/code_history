#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>

using namespace std;

char str[100];

bool is_palindrome(char *str, int len)
{
    int i = 0;
    int j = len - 1;
    while (i < j) {
        if (str[i] != str[j]) {
            return false;
        }
        i++;
        j--;
    }
    return true;
}

int main()
{
    fgets(str, 100, stdin);
    str[strlen(str)-1] = '\0';
    int len = strlen(str);
    if (len == 0) {
        cout << "Invalid input" << endl;
        return 1;
    }
    bool res = is_palindrome(str, len);
    printf("%s %s a palindrome.\n", str, res ? "is" : "is not");
}
