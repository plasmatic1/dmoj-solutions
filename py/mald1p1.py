# ./p1-scratch-cat-and-ddos.yml
l = [input() for _ in range(int(input()))]
flag = [False]*len(l)
for i, s in enumerate(l):
    if 'yubo' in s:
        for j in range(max(0, i-1), min(len(l), i+2)):
            flag[j] = True

for s in list(sorted(set((x for x, f in zip(l, flag) if f)))):
    print(s)