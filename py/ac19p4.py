n = int(input())
pts = set()
best = 0

for _ in range(n):
    pts.add(tuple(map(int, input().split())))

for i in pts:
    for j in pts:
        oth = (i[0], j[1])
        oth2 = (j[0], i[1])

        if oth in pts and oth2 in pts:
            best = max(best, abs(j[0] - i[0]) * abs(j[1] - i[1]))

print(best)