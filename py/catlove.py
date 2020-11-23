cnts = [0, 0]
DIC = {'cats': 0, 'dogs': 1}

for _ in range(int(input())):
    cnts[DIC[input()]] += 1

if cnts[0] > cnts[1]:
    print('cats')
elif cnts[1] > cnts[0]:
    print('dogs')
else:
    print('equal')