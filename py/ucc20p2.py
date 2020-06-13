n = int(input())
mn = int(1e18)
for i in range(n):
    mn = min(mn, sum(list(map(int, input().split()))[1:]))
print(mn)