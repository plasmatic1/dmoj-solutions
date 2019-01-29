from collections import *
import sys

input = lambda: sys.stdin.readline().strip()
print = lambda form, *args: sys.stdout.write((form % args) + '\n')

orddict = OrderedDict
defdict = defaultdict
counter = Counter

def nextint(): return int(input())
def snexts(): return input().split(' ')
def snextint(): return map(int, snexts())
# def array(length, base=0): return [base] * length
# def matrix(length, width, base=0): return [[base] * width for _ in range(length)]

for _ in range(nextint()):
    dic = {}
    currctr = 1

    while 1:
        line = input()

        if line == '':
            break
        else:
            line = line.split(' ')

        l = len(line)
        i = 0
        while i < l:
            if line[i] in dic:
                line[i] = str(dic[line[i]])
            else:
                dic[line[i]] = currctr
                currctr += 1
            i += 1
    
        print(' '.join(line))