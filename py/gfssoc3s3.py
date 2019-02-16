import sys
#from collections import deque, defaultdict
#from math import *
#from heapq import heappush, heappop
input = sys.stdin.readline

def gets(): return input().strip()
def geti(): return map(int, gets().split())
def getf(f=float): return map(f, gets().split())
def gi(): return int(gets())

n = gi()

if n == 1: print(9)
elif n == 2: print(18)
else:
    if n == 17: print(99999998)
    elif n > 17: print(999999998)
    else:
        digc = (n - 1) // 2
        is9 = not (n % 2)

        end = '1' + ('9' if is9 else '0') + '9' * (digc - 1) + '8'
        print(end)
