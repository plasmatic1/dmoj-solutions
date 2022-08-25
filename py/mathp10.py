mod = 10**9 + 7
d2 = (mod + 1) // 2

n = int(input())
ans = 0
for i, x in enumerate(map(int, input().split()), start=-n):
    ans += i**2 * x * d2 % mod

print(ans % mod)