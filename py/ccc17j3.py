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

a, b = snextint()
c, d = snextint()
e = nextint()

delta = abs(c - a) + abs(d - b)

print('Y') if (delta % 2 == e % 2) and (e >= delta) else print('N')