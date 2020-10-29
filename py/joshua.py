mod = int(1e9 + 7)
r, c = map(int, input().split())
print(pow(pow(2, r-1, mod), c-1, mod))