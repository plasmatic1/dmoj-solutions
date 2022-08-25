import math
import sys

input = sys.stdin.readline

def intsqrt(s):
    l = 0
    r = s
    ans = -1

    while l <= r:
        mid = (l + r) // 2
        if mid * mid <= s:
            ans = mid
            l = mid + 1
        else:
            r = mid - 1

    return ans

def gcdExtended(a, b):
    # Base Case
    if a == 0 :
        return b,0,1

    gcd,x1,y1 = gcdExtended(b%a, a)

    # Update x and y using results of recursive
    # call
    x = y1 - (b//a) * x1
    y = x1

    return gcd,x,y

def modinv(a, m):
    g, x, y = gcdExtended(a, m)
    assert g == 1
    return x % m

T = int(input())
assert 1 <= T <= 10**6

for _ in range(T):
    N, e, c1, c2 = map(int, input().split())
    assert 1 <= N <= 10**18
    assert 1 <= e <= 10**18
    assert 0 <= c1 < N
    assert 0 <= c2 < N

    pe = (c1 + c2) * modinv(2, N) % N
    qe = (c1 - pe) % N

    p = math.gcd(pe, N)
    q = math.gcd(qe, N)

    if p > q:
        p, q = q, p

    if p == N:
        p = intsqrt(p)
        q = p

    assert 3 <= p <= 10**18
    assert 3 <= q <= 10**18
    print(p, q)