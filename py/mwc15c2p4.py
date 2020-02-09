import sys
input = sys.stdin.readline
n = int(input())
l = list(map(int, input().split()))
l.sort(reverse=True)
p = []
pre = int(2e9)
for i in l:
    if pre - i <= 1:
        p.append(i)
        pre = int(2e9)
    else:
        pre = i
tot = 0
p.reverse()
while p:
    if len(p) == 1: break
    tot += p.pop() * p.pop()
print(tot)