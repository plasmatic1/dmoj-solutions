from sys import stdin, setrecursionlimit
setrecursionlimit(1000000000)
#input = stdin.readline

n = int(input())
grid = [list(map(int, input().split())) for _ in range(n)]
dis = [[-1] * (n + 1) for _ in range(n + 1)]

def dfs(i, j):
    if dis[i][j] != -1: return dis[i][j]
    
    dis[i][j] = 0
    if i < n - 1 and grid[i + 1][j] < grid[i][j]:
        dis[i][j] = dfs(i + 1, j) + 1
    if i > 0 and grid[i - 1][j] < grid[i][j]:
        dis[i][j] = max(dis[i][j], dfs(i - 1, j) + 1)
    if j < n - 1 and grid[i][j + 1] < grid[i][j]:
        dis[i][j] = max(dis[i][j], dfs(i, j + 1) + 1)
    if j > 0 and grid[i][j - 1] < grid[i][j]:
        dis[i][j] = max(dis[i][j], dfs(i, j - 1) + 1)
    
    return dis[i][j]

best = -1
for i in range(n):
    for j in range(n):
        best = max(best, dfs(i, j))
print(best)