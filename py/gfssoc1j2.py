nn=int(input())
x=0
y=0

def n(v):
    global y
    y += v

def e(v):
    global x
    x += v

def s(v):
    global y
    y -= v

def w(v):
    global x
    x -= v

dirmap = {
    'North' : n,
    'East': e,
    'South': s,
    'West': w
}

for _ in range(nn):
    direc = input()
    amt = int(input())
    dirmap[direc](amt)

print(x, y)