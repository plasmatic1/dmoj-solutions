from collections import *
import sys

input = lambda: sys.stdin.readline().strip()
print = lambda form, *args: sys.stdout.write((form % args) + '\n')

def nextint(): return int(input())
def snexts(): return input().split(' ')
def snextint(): return map(int, snexts())

for _ in range(nextint()):
    n = nextint()
    cnt = 0
    currpwr = 5
    while currpwr <= n:
        cnt += int(n // currpwr)
        currpwr *= 5
    
    print('%d', cnt)