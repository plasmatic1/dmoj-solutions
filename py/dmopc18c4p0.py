import sys
from collections import deque, defaultdict
from functools import reduce
from math import *
input = sys.stdin.readline

def gets(): return input().strip()
def geti(): return map(int, gets().split())

r, x, y = geti()

xa, ya, ma = geti()
xb, yb, mb = geti()
xc, yc, mc = geti()

stars = [(ma, xa, ya), (mb, xb, yb), (mc, xc, yc)]
stars = list(sorted(stars))

m, xs, ys = stars[0]
dx = xs - x
dy = ys - y
dis = sqrt(dx * dx + dy * dy)

if dis < r:
    print('What a beauty!')
else:
    print('Time to move my telescope!')