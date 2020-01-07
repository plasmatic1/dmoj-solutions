import sys;
input=sys.stdin.readline;

s = 'z' + input().strip()
A = ord('a')

lets = [[0] * 1000001 for i in range(26)]

for i in range(1, len(s)):
    if s[i] == ' ':
        continue
    
    ch = ord(s[i]) - A
    lets[ch][i] = 1

for i in range(26):
    for j in range(1, len(s)):
        lets[i][j] += lets[i][j - 1]

for i in range(int(input())):
    a, b, l = input().split()
    a = int(a)
    b = int(b)
    l = ord(l) - A
    
    print(lets[l][b] - lets[l][a - 1])