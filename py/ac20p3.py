# ./appleby-contest-20-p3-ridiculous-string.yml
import sys
MN = 5 * 10**5 + 5;
OA = ord('a')
inf = int(10**9)

N, M = map(int, input().split())
s = input()
T = input()

nxt = [[inf]*26 for _ in range(N+1)]

for i in range(N):
    c = ord(s[i]) - OA
    if nxt[N][c] == inf:
        nxt[N][c] = i
for i in range(N-1, -1, -1):
    c = ord(s[i]) - OA
    for j in range(26):
        nxt[i][j] = nxt[i+1][j]
    nxt[i][c] = i

ans = -1
for i in range(M):
    c = ord(T[i]) - OA
    t = nxt[(ans + 1) % N][c]
    loc = ans % N
    delta = t - loc

    if t == inf:
        print(-1)
        sys.exit(0)
    if delta <= 0: delta += N
    ans += delta
print(ans+1)