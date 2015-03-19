#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>

using namespace std;

char s1[100];
char s2[100];

int substring(char *s1, char *s2)
{
    int in_s1 = 1;
    int mlen = 0;
    int ms_so;

    for (int diff = 0; diff < strlen(s2); diff++) {
        char *s1_temp = s1 + diff;
//        cout << s1_temp << endl;
        int clen = 0;
        int cs_so = 0; 
        int last_eq = 0;
        int ncmp = strlen(s1_temp) >= strlen(s2) ? strlen(s1_temp) : strlen(s2);
        for (int i = 0; i < ncmp; i++) {
            if (s1_temp[i] == s2[i]) {
                clen++;
                if (!last_eq) {
                    cs_so = i;
                }
                if (clen > mlen) {
                    in_s1 = 0;
                    mlen = clen;
                    ms_so = cs_so;
                }
                last_eq = 1;
            } else {
                clen = 0;
                cs_so = 0;
                last_eq = 0;
            }
        }
    }
    
    for (int diff = 0; diff < strlen(s1); diff++) {
        char *s2_temp = s2 + diff;
//        cout << s2_temp << endl;
        int clen = 0;
        int cs_so = 0; 
        int last_eq = 0;
        int ncmp = strlen(s1) >= strlen(s2_temp) ? strlen(s1) : strlen(s2_temp);
        for (int i = 0; i < ncmp; i++) {
            if (s1[i] == s2_temp[i]) {
                clen++;
                if (!last_eq) {
                    cs_so = i;
                }
                if (clen > mlen) {
                    in_s1 = 1;
                    mlen = clen;
                    ms_so = cs_so;
                }
                last_eq = 1;
            } else {
                clen = 0;
                cs_so = 0;
                last_eq = 0;
            }
        }
    }

    cout << "Max substring: \"";
    for (int i = ms_so; i < ms_so + mlen; i++) {
        if (in_s1) {
            cout << s1[i];
        } else {
            cout << s2[i];
        }
    }
    cout << "\", length: " << mlen << endl;

    return mlen;
}

int main()
{
    fgets(s1, 100, stdin);
    fgets(s2, 100, stdin);
    s1[strlen(s1)-1] = '\0';
    s2[strlen(s2)-1] = '\0';
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    if (len1 == 0 || len2 == 0) {
        cout << "Invalid input" << endl;
        return 1;
    }
    int res = substring(s1, s2);
    return 0;
}

