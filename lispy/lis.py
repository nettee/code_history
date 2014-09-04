# Peter Norvig
# (How to Write a (Lisp) Interpreter (in Python))

import sys
import math
import operator

def add_globals(env):
    env.update(vars(math))
    env.update({
        '+' : operator.add,
        '-' : operator.sub,
        '*' : operator.mul,
        '/' : operator.truediv
    })
    return env

class Env(dict):
    """An environment: a dict of {'var':val} pairs,
    with an outer Env. """
    def __init__(self, parms=(), args=(), outer=None):
        self.update(zip(parms, args))
        self.outer = outer
    def find(self, var):
        "Find the innermost Env where var appears."
        if var in self:
            return self
        elif self.outer is None:
            print("Env error")
        else:
            return self.outer.find(var)

global_env = add_globals(Env())

def eval_(x, env=global_env):
    "Evaluate an expression in an environment."
    if isinstance(x, Symbol):   # variable reference
        return env.find(x)[x]
    elif not isinstance(x, list):   # constant literal
        return x
    elif x[0] == 'quote':       # (quote exp)
        (_, exp) = x
        return exp
    elif x[0] == 'if':       # (if test conseq alt)
        (_, test, conseq, alt) = x
        if eval_(test, env):
            return eval_(conseq, env)
        else:
            return eval_(alt, env)
    elif x[0] == 'define':
        (_, var, exp) = x
        env[var] = eval_(exp, env)
    elif x[0] == 'lambda':
        (_, vars, exp) = x
        def func_(*args):
            return eval_(exp, Env(vars, args, env))
        return func_
    else:                      # (proc exp*)
        exps = [eval_(exp, env) for exp in x]
        proc = exps.pop(0)
        return proc(*exps)


def parse(s):
    return read_from(tokenize(s))

def tokenize(s):
    "Convert a string into a list of tokens."
    ss = s.replace('(', ' ( ').replace(')', ' ) ')
    return ss.split()

def read_from(tokens):
    "Read an expression from a seq of tokens."
    if not(tokens):
        print("read token error")
    t = tokens.pop(0)
    if t == '(':
        L = []
        while tokens[0] != ')':
            L.append(read_from(tokens))
        tokens.pop(0)  # pop off ')'
        return L
    elif t == ')':
        print("unexpected )")
    else:
        return atom(t)

def atom(token):
    "Numbers become numbers; every other token is a symbol."
    try:
        return int(token)
    except ValueError:
        try:
            return float(token)
        except ValueError:
            return Symbol(token)

class Symbol(str):
    def __init__(self, s):
        self = s

def to_string(exp):
    if isinstance(exp, list):
        return '(' + ' '.join(to_string(e) for e in exp) + ')'
    else:
        return str(exp)

def repl(prompt='lis.py> '):
    while True:
        val = eval_(parse(input(prompt)))
        if val is not None:
            print(to_string(val))

if __name__ == '__main__':
    repl()

