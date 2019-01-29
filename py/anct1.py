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

MV = 1000000000000

n, d = snextint()
d = abs(d)
minc = MV
for v in snextint():
    v = abs(v)
    if d % v == 0:
        minc = min(minc, d / v)

if minc == MV:
    print('This is not the best time for a trip.')
else:
    print(int(minc))