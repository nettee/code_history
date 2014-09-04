#!/usr/bin/env python3

# version: 0.8.3
# 2013-12-8

""" pandim: html file generator
use yate as support
"""

import sys
import re
import argparse

import yate
    
def pandim(args):
    if args.filename:
        fobj = open(args.filename, 'r')
    else:
        fobj = sys.stdin

    buf = []
    IN_CODE = False
    IN_QUOTE = False

    for line in fobj:
        line = line.rstrip('\n')
        if line.startswith('\\'):
            option = re.search(r'\\(\w+)', line).group(1)
            if option == 'code':
                IN_CODE = True
                buf = []
                continue
            elif option == 'endcode':
                line = yate.code(buf)
                IN_CODE = False
            elif option == 'quote':
                IN_QUOTE = True
                buf = []
                continue
            elif option == 'endquote':
                line = yate.blockquote(buf)
                IN_QUOTE = False
        elif IN_CODE:
            buf.append(line)
            continue
        elif IN_QUOTE:
            buf.append(yate.para(line))
            continue
        elif line.startswith('#'):
            npounds = re.match(r'#+', line).group(0)
            line = line.lstrip('#').lstrip(' ')
            line = yate.header(line, len(npounds))
        elif line.startswith('>'):
            line = line.lstrip('>').lstrip(' ')
            line = yate.blockquote(yate.para(line))
        elif not line:
            continue
        else:
            line = yate.para(line)
        print(line)

    if args.filename:
        fobj.close()

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('filename', nargs='?')
    parser.add_argument('-t', '--title')
    
    return parser.parse_args()

if __name__ == '__main__':
    args = parse_args()
    templ_1 = """<!DOCTYPE html>
    <html lang='zh' xmlns="http://www.w3.org/1999/xhtml">
      <head>
        <meta charset='utf-8' />
        <title>{title}</title>
      </head>
      <body> """
    templ_2 = """</body> </html> """

    if args.title:
        print(templ_1.format(title=args.title))
    else:
        print(templ_1.format(title='a.html'))

    pandim(args)

    print(templ_2)
