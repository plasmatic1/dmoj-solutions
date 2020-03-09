t = int(input())
for _ in range(t):
    n = int(input())
    a = [int(input()),int(input()),int(input())]
    ans = [0] * 3

    for i in range(2, -1, -1):
        sub = min(n, a[i])
        ans[i] = sub
        n -= sub

    if n:
        print(-1)
    else:
        print(' '.join(map(str, ans)))