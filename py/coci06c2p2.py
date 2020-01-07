l=list(sorted(map(int, input().split(' '))))
D={'A': 0, 'B': 1, 'C': 2}
arr=input()
for i in arr:
    print(l[D[i]], end=' ')