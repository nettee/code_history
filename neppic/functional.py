#!/usr/bin/env python3.2 

def add(x, y):
    return x + y

lambda_add = lambda x, y: x + y

add_a_number_to_another_one_by_using_plus_operator = add
# print(add_a_number_to_another_one_by_using_plus_operator(1, 2))

def f():
    n = 1
    def inner():
        nonlocal n
        n = 'x'
    print(n)
    inner()
    print(n)

lst = list(range(5))

def sum_(lst):
    amount = 0
    for num in lst:
        amount = add(amount, num)
    return amount

def reduce_(func, lst, initial):
    result = initial
    for num in lst:
        result = func(result, num)
    return result

def map_(func, lst):
    result = []
    for it in lst:
        result.append(func(it))
    return result

def add_to(n):
    return lambda x: add(n, x)

if __name__ == '__main__':
    lst = map_(lambda x: add(11,x), lst)
    print(reduce_(lambda x, y : x* y , lst, 1))
