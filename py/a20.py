import sys
lines = iter(sys.stdin)

def nexts():
    return next(lines).strip()

def nextint():
    return int(nexts())

def tohex(v):
    return hex(v)[2:].upper().zfill(8)

VAL = 1 << 20
INV = ~VAL

n = nextint()
for _ in range(n):
    ov = nexts()
    v = int(ov, 16)
    if v & VAL:
        print('%s %s' % (tohex(v & INV), ov))
    else:
        print('%s' % ov)