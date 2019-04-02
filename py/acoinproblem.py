import sys
#from collections import deque, defaultdict
#from math import *
#from heapq import heappush, heappop
input = sys.stdin.readline

def gets(): return input().strip()
def geti(): return map(int, gets().split())
def getf(f=float): return map(f, gets().split())
def gi(): return int(gets())

def trd(v): return v[2]

n, v = geti()
coins = [0] + list(geti())
dp = [1000000000] * 10001
qus = []
ans = [0] * v
qptr = 0

for i in range(v):
    qus.append((i,) + tuple(geti()))

qus.sort(key=trd)

dp[0] = 0
for i in range(1, n + 1):
    for j in range(coins[i], 10001):
        dp[j] = min(dp[j], dp[j - coins[i]] + 1)
    
    while qptr < v and qus[qptr][2] == i:
        cq = qus[qptr]
        ans[cq[0]] = dp[cq[1]]
        qptr += 1

for i in ans:
    if i == 1000000000: print(-1)
    else: print(i)