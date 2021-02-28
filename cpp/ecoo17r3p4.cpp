// ./ecoo-17-r3-p4-ice-cream-beach.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

struct pp {
    int x, f;
    bool operator<(const pp &o) const {
        return x < o.x;
    }
};

const ll MOD = 1e9 + 7;
const int MN = 4001, MM = 21, MP = 1e6 + 10;
int N, M;
pp pps[MN];
ll dp[MN][MM], opt[MN], sumw[MP], sumpw[MP];

ll rq(ll a[MP], int l, int r) { return a[r] - a[l-1]; }
ll check(ll p, int l, int r) {
    l = pps[l].x; r = pps[r].x;
    ll res = (rq(sumw, l, p) * p - rq(sumpw, l, p)) + (rq(sumpw, p, r) - rq(sumw, p, r) * p);
    return res;
}

void solve() {
    memset(sumw, 0, sizeof sumw);
    memset(sumpw, 0, sizeof sumpw);

    cin >> N >> M;
    for (auto i = 0; i < N; i++) {
        int x, f; cin >> x >> f;
        sumw[x] += f;
        sumpw[x] += ll(x) * f;
        pps[i] = {x, f};
    }
    for (auto i = 1; i < MP; i++) {
        sumw[i] += sumw[i-1];
        sumpw[i] += sumpw[i-1];
    }

    ll ans = LLINF;
    memset(dp, 0x3f, sizeof dp);
    dp[0][0] = 0;
    for (auto i = 1; i <= N; i++) {
        int ptr = i-1;
        opt[i-1] = 0;
        for (auto j = i-2; j >= 0; j--) {
            while (ptr > j && check(pps[ptr-1].x, j, i-1) < check(pps[ptr].x, j, i-1)) ptr--;
            opt[j] = check(pps[ptr].x, j, i-1);
        }

        for (auto j = 1; j <= M; j++) {
            for (auto k = 0; k < N; k++)
                dp[i][j] = min(dp[i][j], dp[k][j-1] + opt[k]);
            if (i == N) ans = min(ans, dp[i][j]);
        }
    }
    cout << ans%MOD << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T = 10;
    // int T = 3;
    while (T--) solve();

    return 0;
}