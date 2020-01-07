import sys
lines = iter(sys.stdin)

def nexts():
    return next(lines).strip()

def nextint():
    return int(nexts())

def snexts():
    return nexts().split(' ')

def snextint():
    return map(int, snexts())

def array(length, base=0):
    return [base] * length

def matrix(length, width, base=0):
    return [[base] * width for _ in range(length)]


import math
n=nextint()

maxx = -1000
maxy = -1000
maxdist = -1
for _ in range(n):
    x, y = snextint()

    dx = abs(x)
    dy = abs(y)
    dist = math.sqrt(dx * dx + dy * dy)

    if dist > maxdist:
        maxdist = dist
        maxx = x
        maxy = y

print(maxx, maxy)