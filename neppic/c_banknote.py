#!/usr/bin/python3.2


def min_payment_count(cashes, target):

    min_result = 10
    
    proper_limit = []
    for x in cashes:
        upper_limit = target // x
        if upper_limit < 10:
            proper_limit.append(upper_limit)
        else:
            proper_limit.append(9)

    contain = []
    for n in proper_limit:
        contain.append(tuple(range(n + 1)))

    for a in range(proper_limit[0] + 1):
        for b in range(proper_limit[1] + 1):
            for c in range(proper_limit[2] + 1):
                for d in range(proper_limit[3] + 1):
                    for e in range(proper_limit[4] + 1):
                        each_comb = [a, b, c, d, e]
            
                        # calculate dot-multiple
                        dot = 0
                        for i in range(len(each_comb)):
                            dot += each_comb[i] * cashes[i]

                        if dot == target:
                            sumt = 0
                            for x in each_comb:
                                sumt += x
                            if sumt < min_result:
                                min_result = sumt
    return min_result

def average_payment_count(cashes):
    allsum = 0
    for target in range(1, 100):
        allsum += min_payment_count(cashes, target)
    return allsum / 99
        


if __name__ == '__main__':
    print(average_payment_count([1,5,10,20,50]))

