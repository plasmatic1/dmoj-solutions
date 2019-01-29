from collections import *
import sys

input = lambda: sys.stdin.readline().strip()
# print = lambda form, *args: sys.stdout.write((form % args) + '\n')
printo = lambda v: sys.stdout.write(str(v) + '\n')

def nextint(): return int(input())
def snexts(): return input().split(' ')
def snextint(): return map(int, snexts())
# def array(length, base=lambda: 0): return [base()] * length
# def matrix(length, width, base=lambda: 0): return [[base()] * width for _ in range(length)]

def allfor(cs, tn, n, k):
    if k == 0:
        print(cs + ('0' * (n - k)))
        return
    elif n == 0:
        return
    
    allfor(cs + '1', tn, n - 1, k - 1)
    allfor(cs + '0', tn, n - 1, k)

for _ in range(nextint()):
    n, k = snextint()
    
    print('The bit patterns are')
    allfor('', n, n, k)
    print()