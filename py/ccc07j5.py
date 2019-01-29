from collections import *
import sys

input = lambda: sys.stdin.readline().strip()
print = lambda form, *args: sys.stdout.write((form % args) + '\n')
printo = lambda v: sys.stdout.write(str(v) + '\n')

def nextint(): return int(input())
def snexts(): return input().split(' ')
def snextint(): return map(int, snexts())
def array(length, base=lambda: 0): return [base()] * length
def matrix(length, width, base=lambda: 0): return [[base()] * width for _ in range(length)]

truck = [-1, 0, 990, 1010, 1970, 2030, 2940, 3060, 3930, 4060, 4970, 5030, 5990, 6010, 7000, 999999999]
a = nextint()
b = nextint()

for _ in range(nextint()):
    truck.append(nextint())
truck.sort()

motlen = len(truck) - 1
dp = [0] * (motlen + 1)
dp[1] = 1

for i in range(1, motlen):
    incc = 0
    while truck[i + incc] - truck[i] <= b:
        if truck[i + incc] - truck[i] >= a:
            dp[i + incc] += dp[i]
        incc += 1

print('%d', dp[motlen - 1])