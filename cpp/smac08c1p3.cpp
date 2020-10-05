#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int n, k; cin >> n >> k;
    vector<int> C(n), dp(n, 0x3f3f3f3f);
    for (auto &x : C) cin >> x;
    dp[0] = C[0];
    deque<int> dq(1, 0);
    for (int i = 1; i < n; i++) {
        while (dq.front() < i - k) dq.pop_front();
        dp[i] = dp[dq.front()] + C[i];
        while (!dq.empty() && dp[dq.back()] >= dp[i]) dq.pop_back();
        dq.push_back(i);
    }
    cout << dp[n - 1];
    return 0;
}