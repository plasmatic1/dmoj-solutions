# ./back-to-school-17-new-english.yml
inf = int(1e9)
oa = ord('a')

from collections import *
import sys
import heapq
n, m = map(int, input().split())
qs = [[] for _ in range(26)]
for i in range(m):
    c, fre, en = input().split()
    qs[ord(c[0]) - oa].append((int(en) - 1, int(fre)))

for i in range(26):
    qs[i] = deque(sorted(qs[i]))
banqs = []

freq = [0] * 26
ban = [0] * 26

ans = []
for i in range(n):
    while banqs and banqs[0][0] < i:
        e, c = heapq.heappop(banqs)
        ban[c] -= 1

    pick = (inf, inf)
    for j in range(26):
        while qs[j]:
            e, f = qs[j][0]
            if freq[j] < f and e < i:
                print(-1)
                sys.exit(0)
            elif freq[j] == f:
                if e >= i:
                    ban[j] += 1
                    heapq.heappush(banqs, (e, j))
                qs[j].popleft()
            elif freq[j] > f:
                print(-1)
                sys.exit(0)
            else:
                break

        if not ban[j]:
            pick = min(pick, (inf, j))
            if qs[j]:
                e, f = qs[j][0]
                pick = min(pick, (e, j))

    if pick == (inf, inf):
        print(-1)
        sys.exit(0)
    else:
        ans.append(pick[1])
        freq[pick[1]] += 1

for i in range(26):
    while qs[i]:
        e, f = qs[i][0]
        assert e == n-1
        if freq[i] != f:
            print(-1)
            sys.exit(0)
        qs[i].popleft()

print(''.join(map(lambda x: chr(x + oa), ans)))