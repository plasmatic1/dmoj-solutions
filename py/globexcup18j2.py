import sys
import re

input = sys.stdin.readline
def gets(): return input().strip()
def geti(): return map(int, input().split())
def getf(f): return f(input())
def gi(): return int(input())

n = gi()
lis = list(geti())
avg = sum(lis) / n
cnt = 0

for i in lis:
    cnt += i > avg

if cnt > n / 2:
    print('Winnie should take the risk')
else:
    print('That\'s too risky')