import sys
lines = iter(sys.stdin)

def nexts():
    return next(lines).strip()

def nextint():
    return int(nexts())

n = nextint()

digit = ['', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine']
teens = ['ten', 'eleven', 'twelve', 'thirteen', 'fourteen', 'fifteen', 'sixteen', 'seventeen', 'eighteen', 'nineteen']
tens = [None, None, 'twenty', 'thirty', 'forty', 'fifty', 'sixty', 'seventy', 'eighty', 'ninety']

BILLION = 1000000000
MILLION = 1000000
THOUSAND = 1000

def wordlength(n):
    s = ''

    def convp(v):
        if v < 10:
            return digit[v]
        elif v < 20:
            return teens[v - 10]
        elif v < 100:
            return tens[int(v // 10)] + digit[v % 10]
    
        return digit[int(v // 100)] + 'hundred' + convp(v % 100)
    
    if n >= BILLION:
        bills = int(n // BILLION)
        s += convp(bills) + 'billion'
        n -= BILLION * bills
    
    if n >= MILLION:
        mills = int(n // MILLION)
        s += convp(mills) + 'million'
        n -= MILLION * mills

    if n >= THOUSAND:
        thous = int(n // THOUSAND)
        s += convp(thous) + 'thousand'
        n -= THOUSAND * thous

    s += convp(n)

    return len(s)

nextl = n
while nextl != 4:
    nextl = wordlength(nextl)
    print(nextl)