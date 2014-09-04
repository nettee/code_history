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

