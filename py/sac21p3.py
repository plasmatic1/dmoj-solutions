# ./sac-21-p3-demellos-replacement.yml
import math

n, p = map(int, input().split())
a1 = (10**18, '')
a2 = (-10**18, '')

for i in range(n):
    name,*rest=input().split()
    m,cs,e = map(int, rest)
    sc = int(math.floor(4*math.sqrt(m) + 3*cs**p - 4*e))

    a1 = min(a1, (sc,name))
    a2 = max(a2, (sc,name))
print(*reversed(a2))
print(*reversed(a1))