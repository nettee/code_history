#!/usr/bin/env python3.2

import re

def isipv4(s):
    # MAY EXIST FAULT, STOP USE
    sub_patt = (r'0{0,2}[0-9]' # 0-9 
        r'|0?[0-9]{2}' # 10-99 
        r'|1[0-9][0-9]' # 100-199 
        r'|2[0-4][0-9]|25[0-5]') # 200-255
    patt = '^(' + sub_patt + r'\.){3}(' + sub_patt + ')$' # xxx.xxx.xxx.xxx
    return re.search(patt, s) != None

if __name__ == '__main__':
    print(isipv4('1.3.4.2'))
