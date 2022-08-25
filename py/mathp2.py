mod = 10**9 + 7
N = int(input())
print(sum(map(int, input().split())) * pow(2, N-1, mod) % mod)