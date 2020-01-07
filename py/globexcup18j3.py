import sys
import re

input = sys.stdin.readline
def gets(): return input().strip()
def geti(): return map(int, input().split())
def getf(f): return f(input())
def gi(): return int(input())

n = gi()
lis = []
for i in range(n):
    lis.append(gi())
mv = max(lis)

prime = [0, 0] + ([1] * mv)

for i in range(mv + 1):
    if prime[i]:
        for j in range(i + i, mv + 1, i):
            prime[j] = 0

cnt = 0

for i in lis:
    cnt += prime[i] and prime[sum(map(int, list(str(i))))]

print(cnt)