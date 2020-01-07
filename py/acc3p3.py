import sys
from bisect import bisect
#from itertools import permutations
#from math import *
input = sys.stdin.readline

def gets(): return input().strip()
def geti(): return map(int, gets().split())
def getf(f): return map(f, gets().split())
def gi(): return int(gets())

inf = (1<<30)-1+(1<<30)
n = gi()
strs = []
for i in range(n):
    strs.append(gets())

# Attempting algo in O(nlogn)

a = ord('a')
lets = [inf] * 26

for s in strs:
    clets = [0] * 26
    for ch in s:
        clets[ord(ch) - a] += 1

    for i in range(26):
        lets[i] = min(lets[i], clets[i])

# Algo

currs = [-1] * n
allindices = []

for s in strs:
    indices = [[] for i in range(26)]
    slen = len(s)

    for i in range(slen):
        indices[ord(s[i]) - a].append(i)

    allindices.append(indices)

for i in range(25, -1, -1):
    if lets[i] == 0:
        continue

    #print(' -- letter "%s"'%chr(i+a))

    best = inf

    for j in range(n):
        indices = allindices[j]
        curr = currs[j]
        bis = len(indices[i]) - bisect(indices[i], curr)
        best = min(best, bis)

    lets[i] = best

    #print('best of %d'%best)

    if best > 0:
        for j in range(n):
            indices = allindices[j]
            currs[j] = indices[i][bisect(indices[i], currs[j]) + best - 1]
            #print('for j=%d set curr to %d'%(j,currs[j]))

final = ''
for i in range(25, -1, -1):
    final += chr(i + a) * lets[i]

if final:
    print(final)
else:
    print(-1)