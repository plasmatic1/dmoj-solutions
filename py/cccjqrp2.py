level = int(input().split()[-1])
n = int(input())
tot = 0
f=[]
for i in range(n):
    f.append(int(input().split()[-1]))
f.sort()
ftot=0
for i in range(n):
    ol = f[i]
    ftot += ol
    if ftot <= level:
        tot += 1

#assert level >= 0
#assert tot != n
print(n)