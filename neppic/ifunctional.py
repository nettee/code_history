#!/usr/bin/env python
# vim:ft=python

def a_sum(start, end):
    s = 0
    for i in range(start, end + 1):
        s += i
    return s

def f_sum(start, end):
    return reduce(lambda x, y: x + y, range(start, end + 1))

def a_fact(start, end):
    r = 1
    for i in range(start, end + 1):
        r *= i
    return r

def f_fact(start, end):
    return reduce(lambda x, y: x * y, range(start, end + 1))

a_l1 = [x ** 2 for x in range(10)]
f_l1 = map(lambda x: x ** 2, range(10))

a_l2 = [x for x in range(10) if x % 2 == 0]
f_l2 = filter(lambda x: x % 2 == 0, range(10))

a_l3 = [x * 2 for x in range(10) if x % 2 == 0]
f_l3 = map(lambda x: x * 2, filter(lambda x: x % 2 == 0, range(10)))

a_l4 = [x * y for (x, y) in zip(range(4,10),range(6,12))]
f_l4 = map(lambda x, y: x * y, range(4,10), range(6,12))

if __name__ == '__main__':
    print a_l4
    print f_l4
