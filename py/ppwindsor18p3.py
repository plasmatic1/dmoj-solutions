from collections import *
import atexit
import io
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

ROWS = ['qwertyuiop', 'asdfghjkl', 'zxcvbnm']
CHRS = [set() for _ in range(3)]

for i in range(3):
    for ch in ROWS[i]:
        CHRS[i].add(ord(ch))

cnt = 0
for _ in range(nextint()):
    s = input()
    ccnt = array(3, False)

    for ch in s:
        for i, chrr in enumerate(CHRS):
            if ord(ch) in chrr:
                ccnt[i] = True

    if sum(ccnt) == 1:
        cnt += 1

print(str(cnt))