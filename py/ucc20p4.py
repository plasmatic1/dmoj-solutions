input = raw_input
n = int(raw_input())
dp = [int(1e18)] * (n + 1)
val = [-1]
for i in xrange(n):
    val.append(int(raw_input()))
dp[0] = 0
for i in xrange(1, n + 1):
    dp[i] = dp[i - 1] + val[i]
    if i >= 2:
        dp[i] = min(dp[i], dp[i - 2] + val[i - 1] + val[i] - min(val[i - 1], val[i]) // 4)
    if i >= 3:
        dp[i] = min(dp[i], dp[i - 3] + sum(val[i-2:i+1]) - min(val[i-2:i+1]) // 2)
print dp[-1]