def gi():
    return int(input())

v=[gi(), gi(), gi()]

if v[1] >= v[0] and v[2] >= v[1]:
    print('Good job!')
else:
    print('Try again!')