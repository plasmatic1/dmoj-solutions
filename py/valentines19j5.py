# ❤️🧡💛💚💙💜💙💚💛🧡❤️🧡💛💚💙💜💙💚💛🧡❤️🧡💛💚💙💜💙💚💛🧡❤️🧡💛💚💙💜💙💚💛🧡❤️🧡💛💚💙💜

import sys
input = sys.stdin.readline
from collections import defaultdict

n = int(input())
lines = defaultdict(lambda: defaultdict(int))

for _ in range(n):
    m, b = map(int, input().split())
    lines[m][b] += 1

def pairs(x):
    return x * (x - 1) // 2

tot = pairs(n)
for k, d in lines.items():
    cnt = 0
    for _, v in d.items():
        tot += pairs(v)
        cnt += v
    tot -= pairs(cnt)

print(tot)

# 💜💙💚💛🧡❤️🧡💛💚💙💜💙💚💛🧡❤️🧡💛💚💙💜💙💚💛🧡❤️🧡💛💚💙💜💙💚💛🧡❤️🧡💛💚💙💜💙💚💛🧡❤️
# a f f e c