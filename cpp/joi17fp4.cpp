// ./joi-2018-final-p4----commuter-pass.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
#define pb push_back

struct ed {
    int v; ll w;
    bool operator<(const ed &o) const {
        return w > o.w;
    }
};

const int MN = 1e5 + 1;
int N, M, U, V, S, T;
vector<ed> g[MN];
ll dis[MN], dis2[MN];

void dijk(int s, ll d[MN], vector<ed> g[MN]) {
    fill(d, d + N + 1, LLINF);
    priority_queue<ed> pq;
    d[s] = 0; pq.push({s, 0});
    while (!pq.empty()) {
        ed c = pq.top(); pq.pop();
        if (c.w > d[c.v]) continue;
        for (auto to : g[c.v]) {
            ll alt = c.w + to.w;
            if (alt < d[to.v]) {
                d[to.v] = alt;
                pq.push({to.v, alt});
            }
        }
    }
}

set<pair<int, int>> zeroF; // F = forward
bool vis[MN];
void dfs(int c) {
    if (vis[c]) return;
    vis[c] = true;
    for (auto to : g[c]) {
        if (dis[c] - to.w == dis[to.v]) {
            zeroF.emplace(to.v, c);
            dfs(to.v);
        }
    }
}

vector<int> gF[MN];
ll dp[MN];

ll ans = LLINF;
void solve(int c, ll disTo[MN], ll disLeft[MN]) {
    if (dp[c] != -1) return;
    dp[c] = disLeft[c];
    for (auto to : gF[c]) {
        solve(to, disTo, disLeft);
        dp[c] = min(dp[c], dp[to]);
    }
    ans = min(ans, dp[c] + disTo[c]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> S >> T >> U >> V;
    for (int i = 0; i < M; i++) {
        int a, b, c; cin >> a >> b >> c;
        g[a].pb({b, c});
        g[b].pb({a, c});
    }
    dijk(S, dis, g);
    dfs(T);

    dijk(U, dis, g);
    dijk(V, dis2, g);
    for (auto p : zeroF)
        gF[p.first].push_back(p.second);

    ans = dis[V];
    memset(dp, -1, sizeof dp);
    solve(S, dis, dis2);
    memset(dp, -1, sizeof dp);
    solve(S, dis2, dis);

    cout << ans << '\n';

    return 0;
}