from collections import *
import sys

input = lambda: sys.stdin.readline().strip()
print = lambda form, *args: sys.stdout.write((form % args) + '\n')

orddict = OrderedDict
defdict = defaultdict
counter = Counter

def nextint(): return int(input())
def snexts(): return input().split(' ')
def snextint(): return map(int, snexts())
def array(length, base=0): return [base] * length
def matrix(length, width, base=0): return [[base] * width for _ in range(length)]

s = input()
ls = len(s)
dp = array(ls + 1)
chrs = [-1] + list(map(ord, s))

for i in range(1, ls + 1):
    best = -1
    for j in range(0, i):
        if chrs[j] < chrs[i]:
            best = max(best, dp[j])
    
    dp[i] = best + 1

print('%d', 26 - max(dp))