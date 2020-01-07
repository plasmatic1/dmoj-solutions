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

primes = []
from math import sqrt
prime = [True for _ in range(10001)]

for i in range(2, 10001):
    if prime[i]:
        primes.append(i)
        
        for j in range(i * 2, 10001, i):
            prime[j] = False

# Take input
for _ in range(5):
    n = int(input())
    facts = defaultdict(int)

    for i in range(2, n + 1):
        sqi = int(sqrt(i)) + 3

        for j in primes:
            if j > sqi:
                break
            
            while i % j == 0:
                i /= j
                facts[j] += 1
        
        if i > 1:
            facts[i] += 1
    
    print(' * '.join(map(lambda item: '%d^%d' % item, sorted(facts.items()))))