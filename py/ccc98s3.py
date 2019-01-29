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
    direction = 0
    right = 0
    up = 0

    ins = nextint()
    while ins != 0:
        if ins == 1:
            amt = nextint()

            if direction == 0:
                up += amt
            elif direction == 1:
                right += amt
            elif direction == 2:
                up -= amt
            else: # direction == 3
                right -= amt
        elif ins == 2:
            direction = (direction + 1) % 4
        else: # ins == 3
            direction = (direction - 1) % 4
        
        ins = nextint()
    
    # Post Processing
    up = -up
    right = -right

# 2 is right, 3 is left

    def orient(currdir, da, db):
        oa = _orient(currdir, da)
        ob = _orient(currdir, db)

        if len(oa) < len(ob):
            return oa + _orient(da, db)
        else:
            return ob + _orient(db, da)
    
    def _orient(currdir, da):
        if currdir == da:
            return []
        elif currdir == 0 and da == 3:
            return [3]
        elif currdir == 3 and da == 0:
            return [2]
        
        delta = abs(da - currdir)
        
        if delta == 2:
            return [3, 3]
        elif delta == 1:
            if da > currdir:
                return [2]
            else: # da < currdir
                return [3]
    
    # Output
    print('Distance is %d', abs(right) + abs(up))

    if right != 0 and up != 0:
        da = -1
        db = -1
        
        if right > 0 and up > 0: # D=0,1
            da = 0
            db = 1
        elif right > 0 and up < 0: # D=1,2
            da = 1
            db = 2
        elif right < 0 and up > 0: # D=0,3
            da = 0
            db = 3
        else: # right < 0 and up < 0 | D=2,3
            da = 2
            db = 3
        
        dirs = orient(direction, da, db)

        if dirs[:-1]:
            for dirv in dirs[:-1]:
                if dirv == 2:
                    direction = (direction + 1) % 4
                else: # dirv == 3
                    direction = (direction - 1) % 4
                
                print('%d', dirv)
        
        if direction % 2:
            print('1\n%d', abs(right))
        else:
            print('1\n%d', abs(up))
        
        print('%d', dirs[-1])

        if direction % 2:
            print('1\n%d', abs(up))
        else:
            print('1\n%d', abs(right))
    elif right != 0 or up != 0:
        d = -1

        if up > 0:
            d = 0
        elif up < 0:
            d = 2
        elif right > 0: # up == 0
            d = 1
        else:
            d = 3
        
        dirs = _orient(direction, d)

        if dirs:
            for dirv in dirs:
                print('%d', dirv)
        
        if up:
            print('1\n%d', abs(up))
        else:
            print('1\n%d', abs(right))
    
    print('')