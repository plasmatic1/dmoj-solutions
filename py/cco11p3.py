from collections import *
import sys

input = lambda: sys.stdin.readline().strip()
print = lambda form, *args: sys.stdout.write((form % args) + '\n')
printo = lambda v: sys.stdout.write(str(v) + '\n')

def nextint(): return int(input())
def snexts(): return input().split(' ')
def snextint(): return map(int, snexts())
def array(length, base=lambda: 0): return [base() for _ in range(length)]
def matrix(length, width, base=lambda: 0): return [[base()] * width for _ in range(length)]

n, m = snextint()
k = nextint()

from functools import reduce

def search(stsize, endsize, adjlist):
    i = 0
    for adjs in adjlist:
        sets = array(endsize, lambda: False)
        for adj in adjs:
            sets[adj] = True
        
        j = 0
        for adjss in adjlist:
            if i == j:
                continue
            
            cnt = 0

            for adj in adjss:
                if sets[adj]:
                    cnt += 1
            
            if cnt >= 2:
                return False
            
            j += 1
        i += 1
    
    return True
    
    # printo(sets)
adj = array(n, lambda: [])
adj2 = array(m, lambda: [])

for _ in range(k):
    a, b = snextint()
    a -= 1
    b -= 1
    adj[a].append(b)
    adj2[b].append(a)

s1 = search(n, m, adj)
s2 = search(m, n, adj2)

# print('%s %s', s1, s2)

print('YES') if s1 and s2 else print('NO')