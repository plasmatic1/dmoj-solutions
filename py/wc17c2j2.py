mm, mo, mu = map(int, input().split())
m, o, u = map(int, input().split())

m = m // mm
o = o // mo
u = u // mu

print(min(m, o, u))