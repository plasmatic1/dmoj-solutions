#from random import randint, choice, choices, sample, shuffle
#from functools import reduce
#from itertools import permutations
#from bisect import bisect_left, bisect_right, bisect

import sys
from collections import deque, defaultdict
from math import *
input = sys.stdin.readline

def gets(): return input().strip()
def geti(): return map(int, gets().split())
def getf(f=float): return map(f, gets().split())
def gi(): return int(gets())

n = gi()
s = 0

for i in range(n):
    s += gi()

print(float(s) / n)