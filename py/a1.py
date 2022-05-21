for tt in range(int(input())):
    n, s = input().split(maxsplit=1)
    n = int(n)
    print(tt+1, s[:n-1] + s[n:])