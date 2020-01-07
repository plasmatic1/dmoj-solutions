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

L = [1, 11, 111, 1111, 11111, 111111]
n = nextint()
k = nextint()
print(n * L[k])