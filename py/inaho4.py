import sys
import re
from collections import deque

input = sys.stdin.readline
def gets(): return input().strip()
def geti(): return map(int, input().split())
def getf(f): return map(f, input().split())
def gi(): return int(input())

from math import *

n=gi()
a=list(getf(float))
b=list(getf(float))
for i in range(n):
    a[i]-=b[i]
    a[i]*=a[i]
print(sqrt(sum(a)))