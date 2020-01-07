n = int(input())
lis = sorted(list(map(int, input().split())))
half = (n // 2) + (n % 2)
liss = [iter(reversed(lis[:half])), iter(lis[half:])]

print(' '.join([str(next(liss[i % 2])) for i in range(n)]))