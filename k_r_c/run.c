#include <stdio.h>
#include "istring.h"

int main()
{
    char s[100];
    char t[] = "hi,\\t, my nameis\\n...\\n..hoho\\n";
    escape(s, t);
    puts(s);
    return 0;
}
