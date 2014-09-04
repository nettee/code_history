#!/usr/bin/python3.2

"""

harmonious number
    definition:
        containing 3 digits(not all the same), if you lift any out,
        the digit and the left two others are multiple relationship

harmonious_number.py
    find every harmonious number
"""

def is_harmonious_number(digit):
    a, b, c = str(digit)
    if a == b == c:
        return False
    try:
        if not(
                int(b + c) % int(a) 
            or int(a + c) % int(b)
            or int(a + b) % int(c)
            ):
            return True
        else:
            return False
    except ZeroDivisionError:
        return False

if __name__ == '__main__':
    for i in range(100, 1000):
        if is_harmonious_number(i):
            print(i)
