import sys
input = raw_input
N = int(input())
a = [[0] + list(map(int, input().split())) for _ in xrange(N)]
mid = [0]
for i in xrange(1, N):
    tmp = []
    for j in xrange(0, N):
        a[j][i] += a[j][i - 1]
        tmp.append(a[j][i])
    # print(i, tmp)
    tmp.sort()
    mid.append(tmp[(N - 1) // 2])
mid.sort()
truemid = mid[(N - 1) // 2]
# print(mid)
print 'YES'
print ' '.join([str(-truemid) for _ in xrange(N)])