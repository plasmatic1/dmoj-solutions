n, m = map(int, input().split())
lis = list(sorted(map(int, input().split())))
print(sum(lis[m:]))