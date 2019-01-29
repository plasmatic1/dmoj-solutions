from collections import *
import sys
import math

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

a = list(snextint())
b = list(snextint())

for i in range(3):
    a[i] = int(math.sqrt(a[i]))
    b[i] = int(math.sqrt(b[i]))

if a == b:
    print('Dull')
else:
    print('Colourful')