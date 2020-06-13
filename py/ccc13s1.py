yr=int(input()) + 1

while 1:
    syr = str(yr)
    
    p = True

    d=set()
    for i in syr:
        if i in d:
           p = False
           break
        d.add(i)
    if p:
        print(syr)
        break
    
    yr += 1