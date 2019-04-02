n = int(input())

for i in range(n):
    x = format(int(input()), 'b')
    l = len(x)
    m = l % 4
    if m != 0:
        x = x.zfill(4 * (l // 4 + 1))
    part=[]
    for j in range(0, l, 4):
        part.append(x[j:j + 4])
    print(' '.join(part))