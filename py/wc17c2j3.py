n, m = map(int, input().split())
mems = list(map(int, input().split()))

cnt = 0
for i in mems:
    if i >= m:
        cnt += 1

print(min(n, cnt * 2))