from collections import deque

deq = deque()
for c in input():
    if deq and c == ')' and deq[-1] == '(':
        deq.pop()
    else:
        deq.append(c)

if not deq:
    print('YES')
else:
    if len(deq) == 2:
        if deq[0] == deq[1]:
            print('YES')
        else:
            print('NO')
    else:
        print('NO')