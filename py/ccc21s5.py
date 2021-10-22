# ./s5-math-homework.yml
import math
import sys
input = sys.stdin.readline

N, M = map(int, input().split())
rs = []
for i in range(M):
    rs.append(tuple(map(int, input().split())))

dif = [[0]*(N+2) for _ in range(17)]
for l, r, v in rs:
    dif[v][l] += 1
    dif[v][r+1] -= 1
for i in range(1, 17):
    for j in range(1, N+1):
        dif[i][j] += dif[i][j-1]

# print(rs)
# print(dif)

A = []
for i in range(1, N+1):
    a = 1
    for j in range(1, 17):
        if dif[j][i] > 0:
            a = a*j // math.gcd(a, j)
    A.append(a)

lg = int(math.log2(N))
sp = [[0]*N for _ in range(lg+1)]

for i in range(N):
    sp[0][i] = A[i]
for i in range(1, lg+1):
    jmp = 2**(i-1)
    for j in range(0, N - 2**i + 1):
        sp[i][j] = math.gcd(sp[i-1][j], sp[i-1][j+jmp])

def q(l, r):
    bit = int(math.log2(r-l+1))
    return math.gcd(sp[bit][l], sp[bit][r-2**bit+1])

# print(*A)
for l, r, v in rs:
    # print(l, r, v, q(l-1, r-1))
    if q(l-1, r-1) != v:
        print('Impossible')
        sys.exit(0)

print(*A)