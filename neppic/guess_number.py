#!/usr/bin/env python3.2

import random
    
def match(target, current):
    number_count = len([d for d in current if d in target])
    position_count = len([x for i,x in enumerate(current) if target[i] == x])
    return number_count, position_count

def game(ubound):
    target = random.sample(range(1, ubound + 1), 4)

    for round_count in range(1, 10):
        try:
            d = input("Enter 4 numbers, splitted by space:")
            nums = [int(x) for x in d.split()]
            if len(nums) != 4:
                print('invalid input, try again')
                continue
            matches = match(target, nums)
            if matches[0] == 4 and matches[1] == 4:
                print("Congratulations! You've got the right answer", nums)
                return
            else:
                print("[round {0}]:".format(round_count), nums)
                print("{0} correct number(s), in which {1} number(s) at right position".format(*matches))
        except ValueError:
            print("invalid input, try again")
            continue
    else:
        print("Game Over! Tries run out.")

def main():
    print("Guess Number V1.9, Author: William, June 2013")
    # easy:1~6, normal:1~7, hard:1~9
    ubounds = {'e' : 6, 'n' : 7, 'h' : 9}
    while True:
        choice = input("[e]Easy, [n]Normal, [h]Hard, [q]Quit >>")
        if choice == 'q':
            break
        else:
            try:
                ubound = ubounds[choice]
                game(ubound)
            except KeyError:
                print("invalid input, try again")

if __name__ == '__main__':
    main()
