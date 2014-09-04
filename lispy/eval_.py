import environment

class Symbol(str):
    def __init__(self, s):
        self = s

def eval_(x, env=environment.global_env):
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
