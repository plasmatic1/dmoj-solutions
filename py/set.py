n=int(input())
l=[]
for _ in range(n):
    l.append(int(input()))
l.sort()
ans=1
for i in range(1,n):
    ans+=l[i]!=l[i-1]
print(ans)