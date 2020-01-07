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

n, a, r = snextint()

if a == 0:
    print(n)
    exit(0)

maxv = r / a
print(int(min(maxv // 1, n)))