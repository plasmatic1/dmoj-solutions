from collections import *
import sys

input = lambda: sys.stdin.readline().strip()
print = lambda form, *args: sys.stdout.write((form % args) + '\n')
printo = lambda v: sys.stdout.write(str(v) + '\n')

def nextint(): return int(input())
def snexts(): return input().split(' ')
def snextint(): return map(int, snexts())
# def array(length, base=lambda: 0): return [base()] * length
# def matrix(length, width, base=lambda: 0): return [[base()] * width for _ in range(length)]

ceildiv = lambda a, b: int(a // b) + 1 if a % b else int(a // b) 

for _ in range(nextint()):
    n = nextint()

    print('Round 0: %d undefeated, 0 one-loss, 0 eliminated', n)

    alive = n
    oneloss = 0
    elim = 0
    rn = 1
    while elim < n - 1:
        old = oneloss

        elim += int(oneloss // 2)
        oneloss = ceildiv(oneloss, 2)

        if alive > 1:
            oneloss += int(alive // 2)
            alive = ceildiv(alive, 2)
        elif alive == 1:
            if oneloss == 1 and old == oneloss:
                alive = 0
                oneloss += 1
        
        print('Round %d: %d undefeated, %d one-loss, %d eliminated', rn, alive, oneloss, elim)
        rn += 1
    print('There are %d rounds.', rn - 1)