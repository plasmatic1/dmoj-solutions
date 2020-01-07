L = ['a', 'e', 'i', 'o', 'u', 'y']
word = input()
while word != 'quit!':
    if word[-2:] == 'or' and word[-3] not in L:
        print(word[:-2] + 'our')
    else:
        print(word)
    word = input()