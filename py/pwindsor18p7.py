from collections import *
import sys

input = lambda: sys.stdin.readline().strip()
print = lambda form, *args: sys.stdout.write((form % args) + '\n')

def nextint(): return int(input())
def snexts(): return input().split(' ')
def snextint(): return map(int, snexts())
def array(length, base=0): return [base] * length
def matrix(length, width, base=0): return [[base] * width for _ in range(length)]

ls = []
for _ in range(nextint()):
    ns = input()
    ls.append(((ns * 10)[:9], ns))

print(''.join(map(lambda tup: tup[1], reversed(sorted(ls)))))