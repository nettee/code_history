#!/usr/bin/python3.2

import itertools 

def average_payment_count(cashes):
    return sum(
        map(
            lambda target: 
                min(
                    map(
                        sum, 
                        filter(
                            lambda each_comb: 
                                sum(
                                    map(
                                        lambda two: two[0] * two[1], 
                                        zip(each_comb, cashes)
                                    )
                                ) == target, 
                            itertools.product(
                                *(map(
                                    lambda n: 
                                        range(n + 1), 
                                    map(
                                        lambda x: x if x < 10 else 9, 
                                        map(lambda x: target // x, cashes)
                                    )
                                ))
                            )
                        )
                    )
                ), 
            range(1, 100)
        )
    )/ 99
        
if __name__ == '__main__':
    print(average_payment_count([1,5,10,20,50]))

