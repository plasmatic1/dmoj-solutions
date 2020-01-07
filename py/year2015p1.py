import sys

def readline():
    return sys.stdin.readline().rstrip()

format = readline()
cnt = int(readline())

for _ in range(cnt):
    name = readline()
    print format.replace('>', name)