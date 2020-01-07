import sys
input = sys.stdin.readline

cc=0
def cmp(i, j):
    global cc
    cc+=1
    print "C", i + 1, j + 1
    sys.stdout.flush()
    ret = int(input())
    if ret == -1: sys.exit(0)
    return ret


def swp(i, j):
    global cc
    cc+=1
    print "S", i + 1, j + 1
    sys.stdout.flush()
    ret = int(input())
    if ret == -1: sys.exit(0)
    return ret


N = int(input())
for k in xrange(10, 0, -1):
    h = (1 << k) - 1
    for i in xrange(h, N):
        for j in xrange(i, h - 1, -h):
            if cmp(j - h, j):
                break
            swp(j - h, j)
            if not cmp(j - h, j):
                break
        
print 'A'
sys.stdout.flush();