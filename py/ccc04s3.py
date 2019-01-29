from collections import *
import sys
sys.setrecursionlimit((1 << 31) - 1)

input = lambda: sys.stdin.readline().strip()
# print = lambda form, *args: sys.stdout.write((form % args) + '\n')
printo = lambda v: sys.stdout.write(str(v) + '\n')

def nextint(): return int(input())
def snexts(): return input().split(' ')
def snextint(): return map(int, snexts())

import re

matrix = [[[] for _ in range(9)] for _ in range(10)]
cells = [[-1 for _ in range(9)] for _ in range(10)]

A = ord('A')
nextt = deque()

for i in range(10):
    j = 0
    for cell in input().split():
        if re.match('\d+', cell):
            cells[i][j] = int(cell)
        else:
            for child in cell.split('+'):
                matrix[i][j].append((ord(child[0]) - A, int(child[1]) - 1))
            nextt.append((i, j))
        j += 1

vis = [[False for _ in range(9)] for _ in range(10)]

def dfs(x, y):
    if cells[x][y] != -1 or vis[x][y]:
        return cells[x][y]
    
    vis[x][y] = True
    
    total = 0
    for adj in matrix[x][y]:
        v = dfs(*adj)

        if v == -1:
            total = -1
            break
        else:
            total += v
    
    cells[x][y] = total
    return total

for pt in nextt:
    dfs(*pt)

for row in cells:
    for cell in row:
        print(cell, end=' ') if cell != -1 else print('*', end=' ')
    print()