from math import *
t=int(True)
def p(c):
    i=int(c)
    return f'{i}'+str(c-i)[t+t:t+t+t+t+t+t+t]
print(p(pi), p(e))