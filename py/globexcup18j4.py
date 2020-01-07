import sys
import re

input = sys.stdin.readline
def gets(): return input().strip()
def geti(): return map(int, input().split())
def getf(f): return f(input())
def gi(): return int(input())

a, b, c, d, e, n = geti()
mod = 1000000007

dp = {}

def f(x):
    if x == 0:
        return e

    if x in dp:
        return dp[x]

    v = (a * f(x // b)) % mod + (c * f(x // d)) % mod
    dp[x] = v
    return v

print(f(n) % mod)