words = input().split()
res = words
for i, w in enumerate(words):
    if i > 0 and w[0].isupper():
        res[i - 1] += '.'

res[-1] += '.'
print(*res)