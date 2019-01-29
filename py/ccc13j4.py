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

t = gi()
n = gi()
lis = []

for i in range(n):
    lis.append(gi())

lis.sort()

tot = 0
cnt = 0

for i in lis:
    if tot + i <= t:
        cnt += 1
        tot += i

print(cnt)
