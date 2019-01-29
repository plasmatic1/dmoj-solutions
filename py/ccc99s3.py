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
# def array(length, base=0): return [base] * length
# def matrix(length, width, base=0): return [[base] * width for _ in range(length)]

fracs = [['*']]

def build(ind, sz):
    third = int(sz // 3)
    lines = []

    for i in range(third):
        lines.append(fracs[ind - 1][i] * 3)
    
    for i in range(third):
        lines.append(fracs[ind - 1][i] + (' ' * third) + fracs[ind - 1][i])
    
    for i in range(third):
        lines.append(fracs[ind - 1][i] * 3)
    
    fracs.append(lines)

for i in range(1, 6):
    build(i, 3 ** i)

for _ in range(nextint()):
    n = nextint()
    fn = fracs[n]
    b = nextint()
    t = nextint()
    l = nextint()
    r = nextint()
    sz = 3 ** n

    for i in range(sz - t, sz - b + 1):
        print(' '.join(fn[i][l - 1:r]))