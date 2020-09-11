import sys
#from random import randint, choice, choices, sample, shuffle
from collections import deque, defaultdict
from functools import reduce
from math import *
input = sys.stdin.readline

def gets(): return input().strip()
def geti(): return map(int, gets().split())
def getf(f): return map(f, gets().split())
def gi(): return int(gets())

a = gi()
aname = set()

for i in range(a):
    aname.add(gets())

b = gi()
bname = set()

for i in range(b):
    bname.add(gets())

cnt = 0

for name in aname:
    if name in bname:
        cnt += 1

print(cnt)
