import sys
import re

input = sys.stdin.readline
def gets(): return input().strip()
def geti(): return map(int, input().split())
def getf(f): return f(input())
def gi(): return int(input())

n = gi()
cnt = 0

for i in range(n):
    cur = float(gets())
    cnt += (cur - int(cur)) >= 0.5

print(cnt, n - cnt, sep='\n')