import sys

input = sys.stdin.readline

def gets(): return input().strip()
def geti(): return map(int, gets().split())
def getf(f): return map(f, gets().split())
def gi(): return int(gets())

n, m, k, v = geti()

bitc = format(v, 'b').count('1') #hacky

print(pow(2, (n - 1) * k, m))
print(pow(pow(2, n, m) - 1, bitc, m))
print(pow(pow(2, n, m) - 1, k - bitc, m))
