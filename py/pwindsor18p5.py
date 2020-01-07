import sys
lines = iter(sys.stdin)

def nexts():
    return next(lines).strip()

def nextint():
    return int(nexts())

n=nextint()
amt3=int(n//3)
mod=1000000007

if n%amt3==1:
    ans=1
    for _ in range(1,amt3):
        ans *= 3
        ans %= mod
    ans*=4
    print(ans % mod)
else:
    ans=1
    for _ in range(amt3):
        ans *= 3
        ans %= mod
    ans *= (n % amt3) if n % amt3 > 0 else 1
    print(ans % mod)