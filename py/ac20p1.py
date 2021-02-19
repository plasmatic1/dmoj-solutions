for _ in range(int(input())):
    a, b, c = sorted(map(int, input().split()))
    if a**2 + b**2 < c**2:
        print('O')
    elif a**2 + b**2 > c**2:
        print('A')
    else:
        print('R')