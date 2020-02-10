#!/usr/bin/env python3

from functools import reduce
from random import shuffle, randrange

small = 100000
big = 1000000000


def gen(n, q):
    arr = [randrange(-big, big) for i in range(n)]
    shuffle(arr)

    # save = arr.copy()

    def query(l, r):
        return reduce(lambda x, y: x + y, arr[l:r])

    def update(l, r, v):
        for x in arr[l:r]:
            x += v

    print(n, q)
    list(map(lambda x: print(x, end=' '), arr))
    res = []
    for i in range(q):
        l, r = sorted([randrange(small), randrange(small)])
        if randrange(big) & 1:
            print('Q', l + 1, r)
            # res.append(query(l, r))
        else:
            x = randrange(-small, small)
            print('C', l + 1, r, x)
            # update(l, r, x)
    # print(res)


if __name__ == '__main__':
    gen(small, small)
