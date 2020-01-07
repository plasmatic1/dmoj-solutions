n = int(input())

table = { #engrish
    'one': 1,
    'two': 2,
    'three': 3,
    'four': 4,
    'five': 5,
    'six': 6,
    'seven': 7,
    'eight': 8,
    'nine': 9,
    'ten': 10,
    #french oh la la
    'un': 1,
    'deux': 2,
    'trois': 3,
    'quatre': 4,
    'cinq': 5,
    'seis': 6,
    'sept': 7,
    'huit': 8,
    'neuf': 9,
    'dix': 10,
    # asian
    '一': 1,
    '二': 2,
    '三': 3,
    '四': 4,
    '五': 5,
    '六': 6,
    '七': 7,
    '八': 8,
    '九': 9,
    '十': 10
    }

def toi(x):
    try:
        return int(x)
    except:
        return table[x]

for i in range(n):
    a, b = input().split()
    print(toi(a)+toi(b))