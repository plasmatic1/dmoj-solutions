import sys
from collections import defaultdict, deque
from math import *

input = sys.stdin.readline

def gets(): return input().strip()
def geti(): return map(int, gets().split())
def getf(f): return map(f, gets().split())
def gi(): return int(input())

n, m, a, b = geti()
matrix = [[] for i in range(n + 1)]

for i in range(m):
    c, d = geti()
    matrix[c].append(d)
    matrix[d].append(c)
    
deq = deque()
dis = [-1] * (n + 1)

dis[a] = 0
deq.append(a)

while deq:
    cur = deq.popleft()
    cdis = dis[cur]
    
    for adj in matrix[cur]:
        if dis[adj] == -1:
            dis[adj] = cdis + 1
            deq.append(adj)

if dis[b] != -1:
    print('GO SHAHIR!')
else:
    print('NO SHAHIR!')