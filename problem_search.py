import urllib.request as request
import json
import os
from collections import namedtuple, defaultdict

URL = 'https://dmoj.ca/api/problem/list'
CACHE = 'searchutil/problem_cache.json'
OS = os.name

Solution = namedtuple('Solution', 'file lang tags')

# Clears screen
def clearscreen():
    if OS == 'nt':
        os.system('cls')
    else:
        os.system('clear')

# Pause
def pause():
    input('Press ENTER to continue...')

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
        dic[problem['name'].lower()].append(code)
    return dic

# Loads solutions
def loadsolutions(dirname, lang):
    dic = defaultdict(list)
    for fn in os.listdir(dirname):
        spl = fn.split('.')
        dic[spl[0]].append(Solution(dirname + '/' + fn, lang, spl[2:]))
    return dic

# Initialization
print('Loading problem data...')
problems = loadproblems()
print('Loaded %d problems!' % len(problems))

print('Loading solution data...')
solutions = loadsolutions('cpp', 'C++')
solutions.update(loadsolutions('java', 'Java'))
solutions.update(loadsolutions('py', 'Python'))
print('Loaded %d solutions!' % len(solutions))
print()
pause()

clearscreen()
print('Welcome to Plasmatic\'s solution database!')

# Prompting
while True:
    search = input('Input your search: ').lower()
    results = []

    problemcnt = 0
    resultcnt = 0
    for name, codes in problems.items():
        if search in name:
            for code in codes:
                if code in solutions:
                    for solution in solutions[code]:
                        results.append((name, solution))
                        resultcnt += 1
                problemcnt += 1

    clearscreen()
    if resultcnt == 0:
        print('No results found!')
        pause()
        clearscreen()
        continue

    print('Found %d solution(s) and %d total problem(s): ' % (resultcnt, problemcnt))
    print()

    results.sort()
    for i in range(resultcnt):
        name, solution = results[i]
        print('(%d): %s in %s, Tags: %s' % (i, name, solution.lang, ', '.join(solution.tags)))
    print()

    entry = None
    while not entry:
        try:
            idx = int(input('Which solution (number) do you want to view? '))
            entry = results[idx]
        except ArithmeticError: pass
        except IndexError: pass

    clearscreen()
    print('Solution for %s:' % entry[0])
    print()
    
    with open(entry[1].file) as f:
        source = f.read()
        print(source)

    print()
    pause()
    clearscreen()
    
