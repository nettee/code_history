# Peter Norvig
# (How to Write a (Lisp) Interpreter (in Python))

import sys
import parser
import eval_

def to_string(exp):
    if isinstance(exp, list):
        return '(' + ' '.join(to_string(e) for e in exp) + ')'
    else:
        return str(exp)

def repl(prompt='lis.py> '):
    while True:
        val = eval_.eval_(parser.parse(input(prompt)))
        if val is not None:
            print(to_string(val))

if __name__ == '__main__':
    repl()

