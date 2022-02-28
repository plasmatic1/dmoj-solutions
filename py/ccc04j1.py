n = int(input())

l = 0
r = n
ans = -1
while l <= r:
    mid = (l + r) // 2
    if mid**2 <= n:
        l = mid+1
        ans = mid
    else:
        r = mid-1

print(f'The largest square has side length {ans}.')