import urllib.request as request
import json
import os

HANDLE = 'Plasmatic'
URL = 'https://dmoj.ca/api/user/submissions/%s' % HANDLE

def getjson(url):
    with request.urlopen(url) as req:
        data = json.loads(req.read())
    return data

subs = set(map(lambda url: url.split('.')[0], filter(
    lambda url: url.split('.')[1] == 'cpp', os.listdir('./cpp/'))))
notin = []

for subid, sub in getjson(URL).items():
    if sub['language'][:3] == 'CPP' and sub['result'] == 'AC':
        code = sub['problem']
        if code not in subs:
            notin.append(code)

notin = sorted(set(notin))
for code in notin:
    print('"%s" not in repo!' % code)

input('Press ENTER to continue...')
