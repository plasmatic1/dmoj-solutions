import urllib.request as request
import json
import os
from collections import namedtuple, defaultdict

URL = 'https://dmoj.ca/api/problem/list'
CACHE = 'searchutil/problem_cache.json'
OS = os.name

Solution = namedtuple('Solution', 'file lang tags')

HANDLE = 'Plasmatic'
URL2 = 'https://dmoj.ca/api/user/submissions/%s' % HANDLE

def getjson(url):
    with request.urlopen(url) as req:
        data = json.loads(req.read())
    return data

acdcodes = []

for subid, sub in getjson(URL2).items():
    if sub['language'][:4] == 'JAVA' and sub['result'] == 'AC':
        acdcodes.append(sub['problem'])

# Loads raw problem data
def loadproblemdata():
    try:
        with request.urlopen(URL) as req:
            return json.load(req)
    except:
        print('Request failed! Retrieving from problem cache...')
        with open(CACHE) as f:
            return json.load(f)

# Converts raw problem data into the proper format
def loadproblems():
    dic = defaultdict(list)
    for code, problem in loadproblemdata().items():
        dic[problem['name'].lower().replace(' ', '')].append(code)
    return dic

# Loads solutions
def loadsolutions(dirname, lang):
    dic = defaultdict(list)
    for fn in os.listdir(dirname):
        spl = fn.split('.')
        dic[spl[0].lower()].append(Solution(dirname + '/' + fn, lang, spl[2:]))
    return dic

# Initialization
print('Loading problem data...')
dic = loadproblems()
print('Loading javas... ')
solutions = loadsolutions('java', 'Java')

def exist(sol):
    for name, ent in dic.items():
        if sol in name:
            return ent
    return None

for name, solution in solutions.items():
    codes = exist(name)
    if codes:
        print('located codes for name %s: %s' % (name, codes))
        code = codes[0]
        print('code has ac? %s' % (code in acdcodes))
        #cont = input('continue? (y/n): ') == 'y'

        if code in acdcodes:
            os.rename(solution[0].file, 'java/%s.java' % code)
