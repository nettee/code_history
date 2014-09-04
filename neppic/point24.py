#!/usr/bin/env python3.2
# file :calculate 24 points

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
    """Return all possible calculations of the certain 4 integers 
        to 24. 
        Args:  [numbers]: a four-element list, all integers
               [ops]: a three-element list, containing the six
                      lambda functions above
        Return: string, containing the method"""
    ops = [ops_tuple[x] for x in indexes]
    repr_ops_and_nums = [repr_ops_tuple[x] for x in indexes] + numbers
    if ops[0](numbers[0], ops[1](numbers[1], ops[2](numbers[2], \
            numbers[3]))) == 24:
        return '({0} {3} ({1} {4} ({2} {5} {6})))'.format(*repr_ops_and_nums)
    if ops[0](ops[1](numbers[0], numbers[1]), \
            ops[2](numbers[2], numbers[3])) == 24:
        return '({0} ({1} {3} {4}) ({2} {5} {6}))'.format(*repr_ops_and_nums)
    return None

def gnumbers(numbers):
    """Generate numbers:receive a list with 4 integers, return a list 
        containing 24 sub-lists which each has a different sequence of 
        the original list
        Args:   a list, with 4 integers
        Return: a nested list, which has 24 sub-list of 4 integers,
                each having different sequences"""
    result = []
    for _i in range(24):
        result.append([])
    for i in range(24):
        tmp = numbers[:]
        result[i].append(tmp.pop(i//6))
        result[i].append(tmp.pop((i % 6) // 2))
        result[i].append(tmp.pop(i % 2))
        result[i].append(tmp[0])
    return result

def calc(numbers):
    result = []
    for each_set in gnumbers(numbers):
        for i in range(6):
            for j in range(6):
                for k in range(6):
                    try:
                        one_result = calculation(each_set, (i, j, k))
                        if one_result != None:
                            result.append(one_result)
                    except ZeroDivisionError:
                        pass
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
