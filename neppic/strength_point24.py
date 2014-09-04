#!/usr/bin/env python3.2

import sys

# Create six functions, turn operations into functions
a = lambda v1, v2: v1 + v2
s = lambda v1, v2: v1 - v2
rs = lambda v1, v2: v2 - v1
m = lambda v1, v2: v1 * v2
d = lambda v1, v2: v1 / v2
rd = lambda v1, v2: v2 / v1
ops_tuple = (a, s, rs, m, d, rd)
repr_ops_tuple = ('+', '-', '_', '*', '/', '\\')

def calculation(numbers, indexes):
    """Return all possible calculations of the certain 4 integers to 24. 
        Args:  [numbers]: a four-element list, all integers
               [ops]: a 3-element list, containing lambda functions above
        Return: string, containing the method"""
    ops = [ops_tuple[x] for x in indexes]
    repr_ops_and_nums = tuple(repr_ops_tuple[x] for x in indexes) + numbers
    try:
        if ops[0](numbers[0], ops[1](numbers[1], ops[2](numbers[2], \
                numbers[3]))) == 24:
            return '({0} {3} ({1} {4} ({2} {5} {6})))'.format(*repr_ops_and_nums)
        if ops[0](ops[1](numbers[0], numbers[1]), \
                ops[2](numbers[2], numbers[3])) == 24:
            return '({0} ({1} {3} {4}) ({2} {5} {6}))'.format(*repr_ops_and_nums)
    except ZeroDivisionError:
        pass # omit zero division error

def calc(numbers):
    from itertools import permutations, product
    all_res = (calculation(num_set, index_set) 
            for num_set in permutations(numbers)
            for index_set in product(range(6), repeat = 3))
    result = [one_res for one_res in all_res if one_res != None]
    return result
 
def main():
    numbers = [int(i) for i in sys.argv[1:]]
    if len(numbers) == 4:
        for it in calc(numbers):
            print(it)
    else:
        print('Error. Invalid input')

if __name__ == '__main__':
    main()
