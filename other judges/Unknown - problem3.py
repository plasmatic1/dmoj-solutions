import sys
lines = iter(sys.stdin)

def nexts():
    return next(lines).strip()

def nextint():
    return int(nexts())

import math

cnt =0
n=nextint()

while n > 0:
    v=nextint()
    isp=True

    if v % 2 == 0 and v > 2:
        isp = False
    else:
        for i in range(3, min(int(math.sqrt(v)) + 1, v)):
            if v % i == 0:
                isp = False
                break
    
    if not isp:
        cnt += 1
    
    n -= 1

print(cnt)