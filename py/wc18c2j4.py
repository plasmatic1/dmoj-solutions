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

n, m, s = geti()
guards = list(sorted(geti()))
zeroc = 0
cnt = 0

for i in guards:
    if s == 0:
        break

    if i == 0:
        zeroc += 1
    else:
        #print('i=%d zeroc=%d cnt=%d s=%d m=%d'%(i,zeroc,cnt,s,m))
        
        if zeroc >= s - 1:
            cnt += s - 1
            zeroc -= s - 1
            s = 1
        else:
            cnt += zeroc
            s -= zeroc
            zeroc = 0

        s = min(m, s + i - 1)
        cnt += 1

#print('s=%d m=%d zeroc=%d cnt=%d'%(s,m,zeroc,cnt))

if zeroc >= s:
    cnt += s
else:
    cnt += zeroc

print(cnt)
