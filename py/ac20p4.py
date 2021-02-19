# ./appleby-contest-20-p4-philosophy-class.yml
n, m = map(int, input().split())
g = [[] for _ in range(n)]
con = [[False]*n for _ in range(n)]
e = []
for _ in range(m):
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    g[a].append(b)
    g[b].append(a)
    con[a][b] = con[b][a] = True
    e.append((a, b))
INF = int(1e9)
ans = [INF, INF, INF, INF]
def pr(ans):
    print(len(ans))
    print(*map(lambda x: x+1, ans))
base = ans
for i in range(n):
    for j in g[i]:
        for k in g[i]:
            if i != j and i != k and j != k and con[j][k]:
                ans = min(ans, list(sorted((i, j, k))))
if ans != base: pr(ans)
else:
    for a, b in e:
        for c, d in e:
            cur = list(sorted(set((a, b, c, d))))
            if len(cur) == 4:
                ans = min(ans, cur)
    if ans != base: pr(ans)
    else: print(-1)