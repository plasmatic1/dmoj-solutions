// ./joi-20-spring-camp-day-4-p1-capital-city.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;
using T = tuple<int, int, int>;

const int MN = 2e5 + 1;
int N, K,
    C[MN];
vector<int> g[MN], idx[MN];

int sz[MN];
bool block[MN];
int gsz(int c, int p) {
    sz[c] = 1;
    for (auto to : g[c])
        if (to != p && !block[to])
            sz[c] += gsz(to, c);
    return sz[c];
}
int gcent(int c, int p, int lim) {
    for (auto to : g[c])
        if (to != p && !block[to] && sz[to] > lim)
            return gcent(to, c, lim);
    return c;
}

set<int> clrs;
vector<int> cidx[MN], nodes;
bool vis[MN], useClr[MN];
int par[MN];
void setup(int c, int p) {
    cidx[C[c]].push_back(c);
    par[c] = p;
    nodes.push_back(c);
    for (auto to : g[c])
        if (to != p && !block[to])
            setup(to, c);
}

int ans = INF;
void decomp(int c) {
    gsz(c, -1);
    if (sz[c] == 1) {
        if (idx[C[c]].size() == 1)
            ans = 0;
        return;
    }

    int cent = gcent(c, -1, sz[c]/2);
    setup(cent, -1);

    // printf("----- DFS cent=%d\n", c);

    queue<int> q; q.push(cent); vis[cent] = true;
    bool ok = true;
    while (!q.empty()) {
        int c = q.front(); q.pop();
        if (cidx[C[c]].size() != idx[C[c]].size()) {
            ok = false;
            break;
        }

        clrs.insert(C[c]);
        // printf("check c=%d clr=%d\n", c,C[c]);
        if (!useClr[C[c]]) {
            for (auto to : cidx[C[c]]) {
                if (!vis[to]) {
                    vis[to] = true;
                    q.push(to);
                }
            }
            useClr[C[c]] = true;
        }
        if (par[c] != -1 && !vis[par[c]]) {
            vis[par[c]] = true;
            q.push(par[c]);
        }
    }

    if (ok)
        ans = min(ans, (int)clrs.size()-1);
    // reset
    for (auto n : nodes) {
        vis[n] = false;
        useClr[C[n]] = false;
        cidx[C[n]].clear();
    }
    clrs.clear();
    nodes.clear();

    block[cent] = true;
    for (auto to : g[cent])
        if (!block[to])
            decomp(to);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;
    for (auto i = 1; i < N; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (auto i = 1; i <= N; i++) {
        cin >> C[i];
        idx[C[i]].push_back(i);
    }

    decomp(1);
    cout << ans << '\n';

    return 0;
}