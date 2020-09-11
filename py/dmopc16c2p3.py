for _ in range(int(input())):
    n, m = map(int, input().split())
    ma, mb = 0, 0
    for i in range(m):
        a, b = map(int, input().split())
        ma = max(ma, a)
        mb = max(mb, b)
    if ma + mb > n:
        print(-1)
    else:
        print('a' * ma + 'b' * mb + 'a' * (n - ma - mb))