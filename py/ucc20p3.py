n = int(input())
input()
sz = list(map(int, input().split()))
input()
space = input()
pre = 0
maxspace = 0
for i in range(len(space)):
    if space[i] == '1':
        maxspace = max(maxspace, i - pre)
        pre = i + 1
maxspace = max(maxspace, len(space) - pre)
maxtrac = 0
sz.sort()
for s in sz:
    if s <= maxspace:
        maxtrac = s
print((n + maxtrac - 1) // maxtrac)