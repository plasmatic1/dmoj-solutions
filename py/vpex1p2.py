n=int(input())
a=list(map(int,input().split()))
target=sum(a)//n
print(sum(map(lambda x: x != target, a)))