import sys
input = sys.stdin.readline
sys.setrecursionlimit(999999999)
p = 0
dsu = list(range(10**5+10))
parity = [0 for _ in range(10**5+10)]
def rt(x):
    pp = []
    while x != dsu[x]:
        pp.append(x)
        x = dsu[x]
    for y in pp: dsu[y] = x
    return x
for _ in range(int(input())):
    spl = list(map(int, input().split()))
    pre = p
    if spl[0] == 1:
        p += 1
    elif spl[0] == 2:
        p += 1
        parity[p] = parity[pre] ^ 1
        dsu[rt(pre)] = rt(p)
    else:
        x = spl[1]
        print(int(parity[x] == parity[rt(x)]))