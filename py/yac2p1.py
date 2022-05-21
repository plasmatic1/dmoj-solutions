# p1-betting.yml
from fractions import Fraction

for _ in range(int(input())):
        a, b, c, d = map(int, input().split())
        f = Fraction(b, a)
        g = Fraction(d, c)
        if f > 1 + f / g:
            print("YES")
        else:
            print("NO")