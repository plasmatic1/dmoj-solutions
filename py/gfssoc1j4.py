# ./tic-tac-moe.yml
# If this isn't 3 points, I don't know what is!

a, b, c = input()
d, e, f = input()
g, h, i = input()

def win(t):
    def ok(x, y, z):
        return x==t and y==t and z==t
    return ok(a,b,c) or ok(d,e,f) or ok(g,h,i) or ok(a,d,g) or ok(b,e,h) or ok(c,f,i) or ok(a,e,i) or ok(g,e,c)

w1 = win('X')
w2 = win('O')
if w1 and w2: print('Error, redo')
elif w1: print('Timothy')
elif w2: print('Griffy')
else: print('Tie')