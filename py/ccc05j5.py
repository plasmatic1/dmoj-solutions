A = 0 # eval haha

while True:
    s = input()
    if s == 'X': break
    qu = s.replace('B', '(').replace('S', ')').replace('N', '+')
    # print(qu)
    try:
        eval(qu)
        if '()' in qu:
            raise ValueError
        if '(' in s or ')' in s or '+' in s:
            raise ValueError
        print('YES')
    except Exception:
        print('NO')