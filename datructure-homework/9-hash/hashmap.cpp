#include <iostream>

#include "hashmap.h"

using namespace std;

int main()
{
    HashMap<char> m;
    int key;
    char value;
    while (true) {
        cin >> key >> value;
        if (cin) {
            m.put(key, value);
        } else {
            break;
        }
    }

    cout << "Hash table: " << endl;
    m.print_table();

    cout << "Start testing..." << endl;

    m.remove(58);

    cout << "search: ";
    cout << "key " << 58;
    cout << ", value " << m.get(58) << endl;

    cout << "search: ";
    cout << "key " << 77;
    cout << ", value " << m.get(77) << endl;

    cout << "search: ";
    cout << "key " << 90;
    cout << ", value " << m.get(90) << endl;

    cout << "search: ";
    cout << "key " << 40;
    cout << ", value " << m.get(40) << endl;




    
    return 0;
}
