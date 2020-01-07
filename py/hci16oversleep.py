import sys
import collections

input = sys.stdin.readline

n, m = map(int, input().split())
grid = ['' for i in range(n + 1)]
st = ()
end = ()

for i in range(1, n + 1):
    grid[i] = ' ' + input().strip()
    for j in range(1, m + 1):
        if grid[i][j] == 's':
            st = (i, j)
        elif grid[i][j] == 'e':
            end = (i, j)

levels = [[-1] * (m + 1) for i in range(n + 1)]
nextt = collections.deque()
nextt.append(st)

levels[st[0]][st[1]] = 0

while nextt:
    x, y = nextt.popleft()
    lvl = levels[x][y]

    for ax, ay in [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)]:
        if ax <= 0 or ax > n or ay <= 0 or ay > m or levels[ax][ay] != -1 or grid[ax][ay] == 'X':
            continue
        
        levels[ax][ay] = lvl + 1
        nextt.append((ax, ay))

endl = levels[end[0]][end[1]]

if endl == -1:
    print(-1)
else:
    print(endl - 1)