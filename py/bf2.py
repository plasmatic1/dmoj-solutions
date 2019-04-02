s = input()
l = int(input())
sl = len(s)
mins = 'z' * l

for i in range(sl - l):
    mins = min(mins, s[i:i + l])

print(mins)