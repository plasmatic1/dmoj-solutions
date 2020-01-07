n=int(input())

for i in range(n):
    ls=[input(),input(),input()]

    yes=True
    for j, s in enumerate(ls):
        for k, t in enumerate(ls):
            if j == k:
                continue
            
            #T is prefix and suffix
            lent = len(t)
            lens = len(s)
            if lent <= lens:
                if s[:lent] == t or s[-lent:] == t:
                    yes=False
                    break
    if yes:
        print('Yes')
    else:
        print('No')