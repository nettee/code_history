#!/usr/bin/env python3.2
"""grep.py
simulate egrep
receive stdin only, do not support file
"""

import sys
import re

patt = re.compile(sys.argv[1])



for line in sys.stdin.readlines():
    if patt.search(line.strip()) != None:
        print(line, end='')


