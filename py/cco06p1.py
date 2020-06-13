import math
n=int(input())
ans=0
p=[float(input().split()[1]) for _ in range(n)]
p.sort()
for i in range(n-1):
    ans = max(ans, p[i+1]-p[i])
ans = max(ans, 360-p[-1]+p[0])
print(int(math.ceil((360-ans)*12)))