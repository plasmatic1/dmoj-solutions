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
b = gi()
u = gi()
d = gi()

if a < b:
    print(u * (b - a))
else:
    print(d * (a - b))
