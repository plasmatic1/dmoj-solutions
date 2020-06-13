n = int(input())
a = input()
b = input()
ans = 0
for i in range(n):
    ans += a[i] == '0' and b[i] == '0'
print(ans)