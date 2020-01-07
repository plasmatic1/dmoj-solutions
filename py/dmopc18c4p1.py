import sys
from collections import deque, defaultdict
from functools import reduce
from math import *
input = sys.stdin.readline

def gets(): return input().strip()
def geti(): return map(int, gets().split())
def gi(): return int(gets())

n = gi()
om = float(input())
avgs = []

for i in range(n):
    spl = iter(gets().split())
    k = int(next(spl))
    tot = om

    for j in range(k):
        tot += float(next(spl))

    avgs.append(tot)

print(sum(avgs) / n)