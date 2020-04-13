import sys
#from random import randint, choice, choices, sample, shuffle
from collections import deque, defaultdict
#from functools import reduce
#from bisect import bisect_left, bisect_right, bisect
#from itertools import permutations
from math import *
input = sys.stdin.readline

def gets(): return input().strip()
def geti(): return map(int, gets().split())
def getf(f): return map(f, gets().split())
def gi(): return int(gets())

n, l, r = geti()
steps = 1

while l < r:
    mid = (l + r) >> 1

    #print(l, r, mid)

    if mid == n:
        break

    if mid < n:
        l = mid
    else:
        r = mid

    steps += 1

print(steps)