a, b = map(int, input().split(' '))
l = [a + b, a * b, a - b, b - a]

print(max(l))