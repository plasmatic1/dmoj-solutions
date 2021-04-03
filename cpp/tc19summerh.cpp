// ./time-traveller-imaxblue.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

struct ed {
    int v, w;
};
struct evt {
    int i, u, t;
};

const int MN = 1e5 + 1, LG = 17;
int N, M, Q, T,
    X[MN], S[MN], E[MN], W[MN], P[MN]; // X,S,E,W for upd, P (node) for query
vector<ed> g[MN];

// centroid tREE
int sz[MN], cp[MN], lv[MN];
bool block[MN];
ll dis[MN][LG];
int gsz(int c, int p) {
    sz[c] = 1;
    for (auto to : g[c])
        if (to.v != p && !block[to.v])
            sz[c] += gsz(to.v, c);
    return sz[c];
}
int gcent(int c, int p, int lim) {
    for (auto to : g[c])
        if (to.v != p && !block[to.v] && sz[to.v] > lim)
            return gcent(to.v, c, lim);
    return c;
}
void dfs(int c, int p, int lv, ll cdis) {
    dis[c][lv] = cdis;
    for (auto to : g[c]) {
        if (to.v != p && !block[to.v]) {
            dfs(to.v, c, lv, cdis+to.w);
        }
    }
}
int decomp(int c, int clv) {
    gsz(c, -1);
    if (sz[c] == 1) {
        lv[c] = clv;
        return c;
    }
    int lim = sz[c]/2, cent = gcent(c, -1, lim);
    lv[cent] = clv;
    dfs(cent, -1, clv, 0);
    block[cent] = true;
    for (auto to : g[cent]) {
        if (!block[to.v]) {
            cp[decomp(to.v, clv+1)] = cent;
        }
    }
    return cent;
}
// query/upd centroid tree
multiset<ll> best[MN];
priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> opt[MN];
void upd(int u, ll v, bool add) {
    if (add) best[u].insert(v);
    else best[u].erase(best[u].find(v));

    for (int c = u; c != -1; c = cp[c])
        opt[c].emplace(*best[u].begin() + dis[u][lv[c]], u);
}
ll query(int u) {
    ll ans = LLINF;
    for (int c = u; c != -1; c = cp[c]) {
        while (!opt[c].empty() && opt[c].top().first != *best[opt[c].top().second].begin() + dis[opt[c].top().second][lv[c]])
            opt[c].pop();
        if (!opt[c].empty())
            ans = min(ans, opt[c].top().first + dis[u][lv[c]]);
    }
    return ans;
}

using Evt = tuple<int, bool, bool, int>; // time, (in=1, out=0), is update, idx

// 1st linesweep
ll dp[MN], ans[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> Q >> T;
    for (auto i = 0; i < N-1; i++) {
        int a, b, w; cin >> a >> b >> w;
        g[a].push_back({b, w});
        g[b].push_back({a, w});
    }

    // setup centroid tree
    cp[decomp(0, 0)] = -1;
    memset(dp, 0x3f, sizeof dp);
    for (auto i = 0; i < N; i++) best[i].insert(LLINF);

    // build linesweep
    vector<Evt> evt;
    X[M] = 0; S[M] = T+1; E[M] = T; W[M] = 0; dp[M] = 0;
    for (auto i = 0; i <= M; i++) { // include "initial" query
        if (i < M) cin >> X[i] >> S[i] >> E[i] >> W[i]; // don't read update #M (fake update)
        evt.emplace_back(S[i], 1, 1, i);
        evt.emplace_back(E[i], 0, 1, i);
    }
    for (auto i = 0; i < Q; i++) {
        int t, u; cin >> t >> u;
        evt.emplace_back(t, 1, 0, i);
        P[i] = u;
    }

    // linesweep
    sort(evt.begin(), evt.end(), greater<Evt>());
    for (auto [_, in, isupd, i] : evt) {
        if (in) {
            if (isupd) {
                if (i < M)
                    dp[i] = query(X[i]) + W[i];
                upd(X[i], dp[i], true);
            }
            else
                ans[i] = query(P[i]);
        }
        else {
            assert(isupd);
            upd(X[i], dp[i], false);
        }
    }
    // output
    for (auto i = 0; i < Q; i++) 
        cout << (ans[i] == LLINF ? -1LL : ans[i]) << '\n';

    return 0;
}