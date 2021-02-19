# ./dmopc-20-contest-3-p1-present-checking.yml
n = int(input())
l = list(map(int, input().split()))
print(['NO', 'YES'][len(set(l)) == n])