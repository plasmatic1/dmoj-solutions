for _ in range(int(input())):
    n = int(input())
    s = list(map(int, input().split()))
    if n % 2 == 0:
        if min(s) == max(s): print(-1)
        else:
            s.sort()
            l = []
            for a, b in zip(s[:n//2], s[n//2:]):
                l.append(a)
                l.append(b)
            print(*l)
    else:
        print(*sorted(s))