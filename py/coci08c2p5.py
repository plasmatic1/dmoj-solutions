import sys

input = sys.stdin.readline
def gets(): return input().strip()
def geti(): return map(int, input().split())
def gi(): return int(input())

s = gets()
n = len(s)
tot = 1
cnt = 1

for ch in s:
    if ch == 'L' or ch == 'R':
        tot <<= 1
    if ch == 'R':
        tot += cnt
    elif ch == '*':
        tot += (tot << 2) + cnt
        cnt *= 3
    # Do nothing if ch is P

print(tot)