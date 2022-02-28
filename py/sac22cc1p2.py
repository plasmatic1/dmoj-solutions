from math import pi

l, h, w = map(float, input().split())
d = float(input())

rem = l*h*w - (d/2)**2 * pi * h
print(rem)