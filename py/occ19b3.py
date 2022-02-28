n = int(input())

def div4(x): return x % 4 == 0

if div4(n) or div4(n - 3):
    print('Yes')
else:
    print('No')