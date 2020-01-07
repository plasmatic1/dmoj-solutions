import sys
input = sys.stdin.readline


n = int(input())
mod = 10**9
power = n//2
cur = 2*(pow(10, power, mod) - 1) % mod
if n % 2:
    cur = cur + 9*pow(10, power, mod) % mod
print(cur % mod)