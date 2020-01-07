from collections import *
import sys

input = lambda: sys.stdin.readline().strip()
print = lambda form, *args: sys.stdout.write((form % args) + '\n')

def nextint(): return int(input())
def snexts(): return input().split(' ')
def snextint(): return map(int, snexts())
def array(length, base=0): return [base()] * length
def matrix(length, width, base=0): return [[base()] * width for _ in range(length)]

r, c = snextint()
start = tuple(snextint())
end = tuple(snextint())
grid = array(r, lambda: '')
levels = matrix(r, c, lambda: -1)

for i in range(r):
    grid[i] = input()

tpcount = nextint()
tps = []
for i in range(tpcount):
    tps.append(tuple(snextint()))

nextt = deque()
nextt.append(start)
levels[start[0]][start[1]] = 0

while nextt:
    cx, cy = nextt.popleft()
    level = levels[cx][cy]

    for ax, ay in ((cx + 1, cy), (cx - 1, cy), (cx, cy + 1), (cx, cy - 1)):
        if ax < 0 or ax >= r or ay < 0 or ay >= c:
            continue
        
        if grid[ax][ay] == 'X' or levels[ax][ay] != -1:
            continue
        
        nextt.append((ax, ay))
        levels[ax][ay] = level + 1

enddist = levels[end[0]][end[1]]
mindist = enddist
for tpx, tpy in tps:
    if levels[tpx][tpy] != -1:
        mindist = min(mindist, levels[tpx][tpy])

print(str(enddist - mindist))