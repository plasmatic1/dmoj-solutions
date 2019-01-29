from collections import *
import sys

input = lambda: sys.stdin.readline().strip()

orddict = OrderedDict
defdict = defaultdict
counter = Counter

def nextint(): return int(input())
def snexts(): return input().split(' ')
def snextint(): return map(int, snexts())
# def array(length, base=0): return [base] * length
# def matrix(length, width, base=0): return [[base] * width for _ in range(length)]

DIC = {'A': 1, 'A#': 2, 'B': 3, 'C': 4, 'C#': 5, 'D': 6, 'D#': 7, 'E': 8, 'F': 9, 'F#': 10, 'G': 11, 'G#': 12}
DIB = [None, 'A', 'A#', 'B', 'C', 'C#', 'D', 'D#', 'E', 'F', 'F#', 'G', 'G#']
INV = ['root position', 'first inversion', 'second inversion']

a = DIC[input()]
b = DIC[input()]
c = DIC[input()]
l = [a, b, c]

def diff(ll):
    return min(abs(l[1] - l[0]), abs(abs(l[1] - l[0]) - 12)), min(abs(l[2] - l[1]), abs(abs(l[2] - l[1]) - 12))

def cycle(ll):
    return ll[1:] + [ll[0]]

inv = 0
while 1:
    da, db = diff(l)
    # print('inv = %d, da=%d, db=%d' % (inv, da, db))
    # print(l)

    if da == 4 and db == 3:
        print(DIB[l[0]])
        print('major')
        print(INV[inv])
        break
    elif da == 3 and db == 4:
        print(DIB[l[0]])
        print('minor')
        print(INV[inv])
        break
    elif da == 4 and db == 4:
        print(DIB[l[0]])
        print('augmented')
        print(INV[inv])
        break
    elif da == 3 and db == 3:
        print(DIB[l[0]])
        print('diminished')
        print(INV[inv])
        break
    else:
        inv -= 1
        inv %= 3
        l = cycle(l)
    
    if inv > 2:
        break