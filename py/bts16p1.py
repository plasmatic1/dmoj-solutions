import re

line=input()
lowc=len(re.findall('[a-z]', line))
higc=len(re.findall('[A-Z]', line))

if lowc>higc:
    print(line.lower())
elif higc>lowc:
    print(line.upper())
else:
    print(line)