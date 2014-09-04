#include <stdio.h>
#include "imstr.h"

int main()
{
    string s1 = make_string("abc");
    string s2 = make_string("def");
    string s = concat_string(s1, s2);
    print_string(s);
}
