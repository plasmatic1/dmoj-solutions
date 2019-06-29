import urllib.request as request
import json
import os

HANDLE = 'Plasmatic'
URL = 'https://dmoj.ca/api/user/submissions/%s' % HANDLE

def getjson(url):
    with request.urlopen(url) as req:
        data = json.loads(req.read())
    return data

def getsources(folder, ext):
    return set(map(lambda splPath: splPath[0], filter(
    lambda splPath: splPath[1] == ext and len(splPath) == 2, map(
        lambda rawPath: rawPath.split('.'), os.listdir('./%s/' % folder)))))

subs = getsources('cpp', 'cpp')
pysubs = getsources('py', 'py')
notin = []

BANNED_CODES = ['phantomc1', 'acc4p4', 'cpc19c1p4', 'coi06p2']

for subid, sub in getjson(URL).items():
    if sub['result'] == 'AC':
        if sub['points'] != int(sub['points']) and sub['points'] != 0:
            continue
        
        code = sub['problem']

        if code in BANNED_CODES:
            continue
        
        if sub['language'][:3] == 'CPP':
            if code not in subs:
                notin.append('CPP - ' + code)
        elif sub['language'][:2] == 'PY':
            if code not in pysubs:
                notin.append('PY - ' + code)

notin = sorted(set(notin))
for code in notin:
    print('"%s" not in repo!' % code)
input('Press ENTER to continue...')
