// ./bruce’s-brittle-bridges.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

const int MN = 2e5 + 1;
int N,
    comp[MN];
ll V[MN], vsum[MN];
vector<pii> g[MN];
vector<int> g2[MN];
bool vis[MN];

void dfs(int c, int p, int id) {
    vis[c] = true;
    comp[c] = id;
    vsum[id] += V[c];
    for (auto to : g[c])
        if (to.first != p && to.second > 1)
            dfs(to.first, c, id);
}
ll dfs2(int c, int p) {
    ll res = 0;
    for (auto to : g2[c])
        if (to != p)
            res = max(res, dfs2(to, c));
    return res + vsum[c];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (auto i = 1; i <= N; i++) {
        cin >> V[i];
    }
    for (auto i = 1; i < N; i++) {
        int a, b, t; cin >> a >> b >> t;
        g[a].emplace_back(b, t);
        g[b].emplace_back(a, t);
    }
    {
        int ctr = 1;
        for (auto i = 1; i <= N; i++) {
            if (!vis[i])
                dfs(i, -1, ctr++);
        }
    }
    for (auto i = 1; i <= N; i++)
        for (auto to : g[i])
            if (comp[i] != comp[to.first])
                g2[comp[i]].push_back(comp[to.first]);

    cout << dfs2(1, -1) << '\n';

    return 0;
}