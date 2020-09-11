import sys
from random import randint, choice, choices, sample, shuffle
from collections import deque, defaultdict
from functools import reduce
from itertools import permutations
from math import *
input = sys.stdin.readline

def gets(): return input().strip()
def geti(): return map(int, gets().split())
def gi(): return int(gets())

tokens = gets().split('-')
ffinal = []
vowels = list('aeiou')

for token in tokens:
    lastconst = ''
    line = ''
    for ch in token:
        if ch in vowels:
            line += lastconst + ch
            lastconst = ''
        else:
            if lastconst == '':
                lastconst = ch
    line += lastconst
    ffinal.append(line)

final = []
last = None
for token in ffinal:
    if token != last:
        last = token
        final.append(token)

print('-'.join(final))
