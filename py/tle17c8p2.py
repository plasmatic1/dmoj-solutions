import sys
#from random import randint, choice, choices, sample, shuffle
from collections import deque, defaultdict, namedtuple
from functools import reduce
from itertools import permutations
from math import *
input = sys.stdin.readline

sys.setrecursionlimit(999999999)

def gets(): return input().strip()
def geti(): return map(int, gets().split())
def getf(f): return map(f, gets().split())
def gi(): return int(gets())

h, d, e = geti()
tot = 0
tottime = -1
modes = []
dpss = [0] * 10000

for i in range(d):
    ai, si = geti()
    modes.append((1 - ai / 100, si))

for i in range(e):
    ti, li, xi = geti()
    dpss[ti] += xi
    dpss[ti + li] -= xi
    tottime = max(tottime, ti + li)

for i in range(1, tottime + 1):
    dpss[i] += dpss[i - 1]

for i in range(0, tottime):
    best = dpss[i]
    for a, s in modes:
        best = min(best, (dpss[i] - s) * a)

    #print('time=%d best=%d dmg=%d'%(i,best,dpss[i]))
    tot += max(best, 0)

left = h - tot

if left > 0:
    print('%.2f' % left)
else:
    print('DO A BARREL ROLL!')