# appleby-contest-20-p2-playful-playdoughs.yml

import sys
input = sys.stdin.readline
N, Q = map(int, input().split())
fre = [0] * (10**5 + 1)
for x in map(int, input().split()):
    fre[x] += 1
for _ in range(Q):
    t, v = map(int, input().split())
    if t == 1:
        fre[v//2] += fre[v]
        fre[(v+1)//2] += fre[v]
        fre[v] = 0
    else:
        print(fre[v])