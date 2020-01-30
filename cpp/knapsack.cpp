#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MW = 5001;
int n, m;
ll dp[2][MW];
deque<int> dqs[MW];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        ll num, cost, value;
        cin >> num >> cost >> value;

        int pre = i & 1, cur = pre ^ 1;
        memset(dp[cur], 0, sizeof dp[cur]);

        // comparison function for sliding window deque.  Calculates the result of transition to dp[i] from dp[j]
        function<ll(int, int)> fun = [&] (int from, int to) { 
            return dp[pre][from] + (to - from) / cost * value;
        };

        // reset sliding window deque
        for (int j = 0; j < MW; j++)
            dqs[j].clear();
        dqs[0].push_back(0);
        
        // do dynamic programming
        for (int j = 0; j < MW; j++) {
            // advance sliding window forwards
            auto &dq = dqs[j % cost];   
            while (!dq.empty() && dq.front() < j - num * cost)
                dq.pop_front();
            
            // update sliding window to include index j
            while (!dq.empty() && fun(dq.back(), j) < dp[pre][j])
                dq.pop_back();
            dq.push_back(j);

            // do dp
            if (!dq.empty()) // take current type of item
                dp[cur][j] = fun(dq.front(), j);
            else // do not take current type of item
                dp[cur][j] = max(dp[cur][j], dp[pre][j]);
        }
    }

    // answer queries
    int cur = ((n - 1) & 1) ^ 1; // final dp array
    
    // sometimes its better to take less :)
    for (int i = 1; i < MW; i++)
        dp[cur][i] = max(dp[cur][i - 1], dp[cur][i]);
    
    ll best = LLONG_MIN;
    for (int i = 0; i < m; i++) {
        int capacity, cost;
        cin >> capacity >> cost;
        best = max(best, dp[cur][capacity] - cost);
    }
    cout << best << '\n';

    return 0;
}