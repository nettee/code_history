def median(L):
    '''求指定列表的中位数'''

    L.sort()
    n = len(L)
    if n % 2:
        result = L[(n-1)//2]
    else:
        a = L[n//2-1]
        b = L[n//2]
        result = (a + b)/2

    return result

if __name__ == '__main__':
    print(median([1,2,3,4,6,7,8]))
    print(median([1,2,3,4,6,7,9,8]))

