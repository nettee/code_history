#include <iostream>
#include "slist.h"

using namespace std;

int main()
{
	slist<int> *a = new slist<int>();
    a->input();

    slist<int> *c = new slist<int>();

    reverse(a, c);

    c->output();

	delete a;
    delete c;
}

