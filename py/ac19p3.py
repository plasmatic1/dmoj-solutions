import re
print(sum([int(x) for x in re.sub(r'[\(\)\+]', '', input()).split()]))