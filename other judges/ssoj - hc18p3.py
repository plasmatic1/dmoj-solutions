import sys
#from random import randint, choice, choices, sample, shuffle
from collections import deque, defaultdict
#from functools import reduce
#from bisect import bisect_left, bisect_right, bisect
#from itertools import permutations
from math import *
input = sys.stdin.readline

def gets(): return input().strip()
def geti(): return map(int, gets().split())
def getf(f): return map(f, gets().split())
def gi(): return int(gets())

n, m = geti()
words = []

for i in gets().split():
    words.append(i)

for encr in gets().split():
    mindiff = 1000000000
    best = ''

    le = len(encr)
    
    for word in words:
        lw = len(word)
        dp = [[1000000] * (lw + 1) for i in range(le + 1)]
        dp[0][0] = 0

        for i in range(1, le + 1):
            dp[i][0] = i

        for i in range(1, lw + 1):
            dp[0][i] = i

        for i in range(1, le + 1):
            for j in range(1, lw + 1):
                if encr[i - 1] == word[j - 1]:
                    dp[i][j] = dp[i - 1][j - 1]
                else:
                    dp[i][j] = min(dp[i][j - 1] + 1, dp[i - 1][j] + 1)

        cmv = dp[le][lw]
    
        #print('\n'.join(map(str, dp)))
        #print('encr=%s word=%s cmv=%d'%(encr,word,cmv))

        if cmv < mindiff:
            mindiff = cmv
            best = word

    print(best, end=' ')

print()
