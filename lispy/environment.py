import math
import operator
import exception

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

def add_globals(env):
    env.update(vars(math))
    env.update({
        '+' : operator.add,
        '-' : operator.sub,
        '*' : operator.mul,
        '/' : operator.truediv
    })
    return env


global_env = add_globals(Env())

