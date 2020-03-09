def shift(x):
    ret = ''
    for ch in x:
        if ch == 'z':
            ret += 'a'
        elif ch == ' ':
            ret += ' '
        else:
            ret += chr(ord(ch) + 1)
    return ret

n=int(input())
l=int(input())
s = input()

for _ in range(l % 26):
    s = shift(s)

print(s)