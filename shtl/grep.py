#!/usr/bin/python3.2

# version: 0.1.2
# 2013-11-19

"""
    slightly different from Unix grep
    meant to be simple
"""

import sys
import re
import argparse

import stil

def grep(fobj, args, pre=None):
    if pre is None:
        prefix = ''
    else:
        prefix = pre + ':'

    pattern = args.pattern

    for line in fobj:
        line = line.rstrip('\n')
        if re.search(pattern, line):
            print(prefix, end='')
            print(line)


def parse():
    parser = argparse.ArgumentParser(
            description='print lines matching a pattern')
    parser.add_argument('pattern')
    parser.add_argument('files', nargs='*')

    return parser.parse_args()

if __name__ == '__main__':
    args = parse()
    file_content = stil.fopen(args.files)

    if len(file_content) == 1:
        grep(file_content[0], args)
    else:
        for fobj in file_content:
            grep(fobj, args, pre=fobj.name)

    stil.fclose(file_content)
