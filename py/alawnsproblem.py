for _ in range(int(input())):
    n, v = map(int, input().split())
    A = list(map(int, input().split()))
    mn = min(A)
    mx = -1
    As = list(sorted(A))
    for i in range(n):
        if A[i] != As[i]:
            mx = max(mx, A[i])
    if mx == -1: print(0)
    else: print(mn - min(mn, v // mx))