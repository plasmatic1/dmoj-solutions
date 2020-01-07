import sys

input = lambda: sys.stdin.readline().strip()

s = input()
ls = len(s)
dp = [0] * (ls + 1)
chrs = [-1] + list(map(ord, s))

for i in range(1, ls + 1):
    best = -1
    for j in range(0, i):
        if chrs[j] < chrs[i]:
            best = max(best, dp[j])
    
    dp[i] = best + 1

print(26 - max(dp))