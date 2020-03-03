#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

struct Qu {
    int l, r, t;
};

const int MN = 1e4 + 1, MT = 101;
int N, Q,
    w[MN], v[MN];

int dp[MN][MT];

// divide and conquer
ll solve(int L, int R, vector<Qu> qus) {
    if (L > R) assert(qus.empty());
    if (qus.empty()) return 0LL;
    int mid = (L + R) / 2;

    vector<Qu> lhs, rhs;
    ll ret = 0;

    // precompute
    for (int i = L - 1; i <= R; i++)
        fill(dp[i], dp[i] + MT, 0);
    for (int i = mid; i <= R; i++)
        for (int j = 0; j < MT; j++)
            dp[i][j] = max(dp[i - 1][j], j < w[i] ? 0 : (dp[i - 1][j - w[i]] + v[i]));
    if (L < mid) {
        for (int i = 0; i < MT; i++)
            dp[mid - 1][i] = i < w[mid - 1] ? 0 : v[mid - 1];
        for (int i = mid - 2; i >= L; i--)
            for (int j = 0; j < MT; j++)
                dp[i][j] = max(dp[i + 1][j], j < w[i] ? 0 : (dp[i + 1][j - w[i]] + v[i]));
    }

    // answer queries
    for (auto &qu : qus) {
        if (qu.l <= mid && qu.r >= mid) {
            vector<int> ans(dp[qu.r], dp[qu.r] + MT);
            if (qu.l < mid) {
                for (int i = MT - 1; i >= 0; i--)
                    for (int j = 0; j <= i; j++)
                        ans[i] = max(ans[i], ans[i - j] + dp[qu.l][j]);
            }
            // printf("l=%d r=%d t=%d a=%d mid=%d\n", qu.l, qu.r, qu.t, ans[qu.t], mid);
            ret += ans[qu.t];
        }
        // propagate queries that are not being answered
        else if (qu.r < mid) lhs.push_back(qu);
        else if (qu.l > mid) rhs.push_back(qu);
    }

    ret += solve(L, mid - 1, lhs) + solve(mid + 1, R, rhs);
    return ret;
}

// dp shit
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> w[i] >> v[i];
    }

    // input queries
    vector<Qu> qus;
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        int l, r, t;
        cin >> l >> r >> t;
        qus.push_back({l, r, t});
    }
    
    // solve
    ll ans = solve(1, N, qus);
    cout << ans << endl;

    return 0;
}