#!/usr/bin/python3.2

from itertools import product

def dotmul(a, b):
    return sum((x * y) for (x, y) in zip(a, b))

def comb(upper_limit):
    contain = []
    for n in upper_limit:
        contain.append(tuple(range(n + 1)))
    return product(*contain)

def min_payment_count(cashes, target):
    upper_limit = tuple(target // x for x in cashes)
    proper_limit = tuple(x if x < 10 else 9 for x in upper_limit)

    correct_result = []
    for each_comb in comb(proper_limit):
        if dotmul(each_comb, cashes) == target:
            correct_result.append(sum(each_comb))
    return min(correct_result)

def average_payment_count(cashes):
    all_result = [min_payment_count(cashes, target)
            for target in range(1, 100)]
    return sum(all_result) / 99
        
def best_banknote():
    mini = 10
    best_sch = None
    for each_sch in product(range(15,50), range(10,40), range(5,20), range(2,10), [1]):
        ave = average_payment_count(each_sch)
        if ave < mini:
            mini = ave
            best_sch = each_sch
    return best_sch


if __name__ == '__main__':
    print(average_payment_count([1,5,10,20,50]))

