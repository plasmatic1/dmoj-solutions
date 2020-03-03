import sys
input = sys.stdin.readline

# Prefix sum
def psum(arr):
    l = len(arr)
    for i in range(1, l):
        arr[i] += arr[i - 1]
# Preprocess
def table_for_sides(sides):
    if not sides: return None

    times = 20
    max_val = times * sides
    dp = [[0] * (max_val + 5) for _ in range(times + 1)]
    dp[0][0] = 1
    for i in range(times):
        # calculate dp and pref. sum
        for j in range(max_val - sides + 1):
            if not dp[i][j]: continue
            div = dp[i][j] / sides
            dp[i + 1][j + 1] += div
            dp[i + 1][j + sides + 1] -= div
        psum(dp[i + 1])
        # print(dp[i + 1])
    return dp

tables = [table_for_sides(i) for i in range(21)]

for _ in range(int(input())):
    H, S = map(int, input().split())
    best = 0.0
    for roll in input().split():
        # Get Input
        times, __ = roll.split('d')
        times = int(times)
        if '+' in __:
            sides, add = map(int, __.split('+'))
        elif '-' in __:
            sides, add = map(int, __.split('-'))
            add *= -1
        else:
            sides = int(__)
            add = 0
        
        # Max per spell
        if H - add < len(tables[sides][times]):
            prob = sum(tables[sides][times][max(0, H - add):])
            best = max(best, prob)

    print('Case #%d: %.8f' % (_ + 1, best))