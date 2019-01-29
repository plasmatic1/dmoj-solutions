from collections import *
import sys

input = lambda: sys.stdin.readline().strip()
print = lambda form, *args: sys.stdout.write((form % args) + '\n')

orddict = OrderedDict
defdict = defaultdict
counter = Counter

def nextint(): return int(input())
def snexts(): return input().split(' ')
def snextint(): return map(int, snexts())
# def array(length, base=0): return [base] * length
# def matrix(length, width, base=0): return [[base] * width for _ in range(length)]

for _ in range(nextint()):
    r = nextint()
    c = nextint()
    grid = []

    for _ in range(r):
        grid.append(input())
    
    dist = [[-1 for _ in range(c)] for _ in range(r)]
    nextt = deque()
    
    nextt.append((0, 0))
    dist[0][0] = 1

    while nextt:
        cx, cy = nextt.popleft()
        dx = dist[cx][cy]

        adjs = ()

        if grid[cx][cy] == '+':
            adjs = ((cx + 1, cy), (cx - 1, cy), (cx, cy + 1), (cx, cy - 1))
        elif grid[cx][cy] == '|':
            adjs = ((cx + 1, cy), (cx - 1, cy))
        elif grid[cx][cy] == '-':
            adjs = ((cx, cy + 1), (cx, cy - 1))
        
        for ax, ay in adjs:
            if ax < 0 or ax >= r or ay < 0 or ay >= c or dist[ax][ay] != -1:
                continue
            
            dist[ax][ay] = dx + 1
            nextt.append((ax, ay))
    
    # Printing out

    if grid[r - 1][c - 1] == '*':
        print('-1')
    else:
        print('%d', dist[r - 1][c - 1])