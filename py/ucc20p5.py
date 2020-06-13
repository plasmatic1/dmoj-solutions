from collections import deque
n, A, B, m = map(int, input().split())
A -= 1
B -= 1
g = [[] for _ in range(n)]
dis = [-1] * n
for i in range(m):
    a, b = map(lambda x: int(x) - 1, input().split())
    g[a].append(b)
Q = deque()
Q.append(A)
dis[A] = 0
while Q:
    c = Q.popleft()
    for to in g[c]:
        if dis[to] == -1:
            dis[to] = dis[c] + 1
            Q.append(to)
print(dis[B])