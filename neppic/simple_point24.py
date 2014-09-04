#!/usr/bin/env python3.2
# file :calculate 24 points

# Create six functions, turn operations into functions
a = lambda v1, v2: v1 + v2
s = lambda v1, v2: v1 - v2
m = lambda v1, v2: v1 * v2
d = lambda v1, v2: v1 / v2
ops_tuple = (a, s, m, d)
repr_ops_tuple = ('+', '-', '*', '/')

def calculation(numbers, indexes):
    ops = [ops_tuple[x] for x in indexes]
    repr_ops_and_nums = [repr_ops_tuple[x] for x in indexes] + numbers
    if ops[0](numbers[0], ops[1](numbers[1], ops[2](numbers[2], \
            numbers[3]))) == 24:
        return '24 = {3} {0} ({4} {1} ({5} {2} {6}))'.format(*repr_ops_and_nums)
    if ops[0](ops[1](numbers[0], numbers[1]), \
            ops[2](numbers[2], numbers[3])) == 24:
        return '24 = ({3} {1} {4}) {0} ({5} {2} {6})'.format(*repr_ops_and_nums)
    return None

def gnumbers(numbers):
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
        for i in range(4):
            for j in range(4):
                for k in range(4):
                    try:
                        one_result = calculation(each_set, (i, j, k))
                        if one_result != None:
                            result.append(one_result)
                    except ZeroDivisionError:
                        pass
    return result
 
def main():
    import random
    _d = random.sample(range(2,20), 4)
    print('Selected digits:', _d)
    _tmp = input('Press ENTER to continue...')
    digits = [int(x) for x in _d]
    res = calc(digits)
    if res != []:
        for it in res:
            print(it)
    else:
        print('no answer found')

if __name__ == '__main__':
    main()
