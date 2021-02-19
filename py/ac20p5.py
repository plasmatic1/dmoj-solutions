# ./appleby-contest-20-p5-ridiculous-tree.yml
from collections import Counter

MN = 4 * 10**5 + 10
N = int(input())
g = [[] for _ in range(N+1)]
sz = [0]*(N+1)


# difference array
ssum = [0]*MN

# get subtree sizes
for i, p in enumerate(map(int, input().split()), 2):
    g[p].append(i)
for i in range(N, 0, -1):
    sz[i] = 1
    for to in g[i]:
        sz[i] += sz[to]

# sieve
jmp = list(range(MN))
pf = [[] for _ in range(MN)]
# do sieve and compute prime factorization of numbers 1..N
for i in range(2, N+1):
    if jmp[i] == i:
        for j in range(i*2, N+1, i):
            jmp[j] = i
for i in range(2, N+1):
    c = i
    while c > 1:
        pf[i].append(jmp[c]);
        c //= jmp[c]

# compute answer in terms of a bunch of factorials
for i in range(1, N+1):
    ssum[sz[i] - 1] += 1
    for to in g[i]:
        ssum[sz[to]] -= 1
for i in range(N-1, 0, -1):
    ssum[i] += ssum[i+1]

# compute answer
ans = Counter()
for i in range(1, N+1):
    for f in pf[i]:
        ans[f] += ssum[i]
# remove entries that are "0"
for k, v in tuple(ans.items()):
    if v == 0:
        del ans[k]
# print
print(len(ans))
for k, v in ans.items():
    print(k, v)