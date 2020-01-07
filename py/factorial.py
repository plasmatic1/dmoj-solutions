mod=1<<32
fact=[-1 for _ in range(129)]

def factorial(v):
    factv=1
    
    for i in range(2,v+1):
        factv=(factv*i)%mod
    
    return factv
        

for _ in range(int(input())):
    n=int(input())
    
    if n >= 128: print(0) # Number is divisible by mod
    else: print(factorial(n))