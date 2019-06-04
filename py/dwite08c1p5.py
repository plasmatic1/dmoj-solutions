import sys
from math import ceil
input = sys.stdin.readline

def gets(): return input().strip()
def geti(): return map(int, input().split())
def gi(): return int(input())

t = 5

for _ in range(t):
    n = gi()
    tot = 0
    for i in range(n):
        cln = gets()
        while cln != '':
            tot += cln.count('#')
            cln = gets()

    print(int(ceil(tot / 25)))
