from math import *
n=3
primes=[2]
while n<100:
    isp=True
    nsqrt=sqrt(n)
    for prime in primes:
        if prime > nsqrt:
            break
        if n%prime==0:
            isp=False
            break
    if isp:
        primes.append(n)
    n+=1
l=len(primes)
for _ in range(5):
    i = int(input())
    cpi=-1
    for j in range(l):
        if primes[j]>=i:
            cpi=j
            break
    ra=primes[cpi-2]
    rb=-1
    if i in primes:
        rb=primes[cpi+2]
    else:
        rb=primes[cpi+1]
    da=i-ra
    db=rb-i
    #print('i: %d, ra %d rb %d da %d db %d mid %d'%(i,ra,rb,da,db,primes[cpi]))
    if da<db:
        print(ra)
    else:
        print(rb)