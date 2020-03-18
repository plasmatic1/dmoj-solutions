T = int(input())
def f(x):
    return x // 2 - x // 7
l = 1
r = 10**18
while l + 1 < r:
    mid = (l + r) // 2
    if f(mid) > T: r = mid
    else: l = mid
for i in range(l, l + 100):
    if f(i) <= T:
        l = i
print(l)