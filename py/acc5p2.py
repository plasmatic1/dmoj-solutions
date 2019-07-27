s = input()

def anyIn(l, s):
    for ss in l:
        if ss in s:
            return True
    return False

if 'DMOJ' in s:
    print(0)
elif ('MOJ' in s) or ('DMO' in s) or ('DMJ' in s) or ('DOJ' in s):
    print(1)
elif anyIn(['DM', 'DO', 'DJ', 'MO', 'MJ', 'OJ'], s):
    print(2)
else:
    print(3)
