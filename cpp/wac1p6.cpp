// ./wesleys-anger-contest-1-problem-6-colourful-cactus-ordeal.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

struct Comp {
    int sz, rt, cid;
    vector<int> ns;
    vector<pii> es;
    unordered_map<int, int> idx;
    int qdis(int a, int b) {
        a = idx[a]; b = idx[b];
        if (a > b) swap(a, b);
        return min(b-a, sz-b+a);
    }
};

const int MN = 1e5 + 1, TH = 450;
int N, M;
vector<int> clrNodes[MN];

// graphs
vector<int> g[MN], _cg[MN*2];
vector<pair<int, int>> cg[MN*2];

// tarjan stuff
int low[MN], ord[MN], cord = 0, csz = 0;
vector<pair<int, int>> stk;
vector<Comp> comps;
void tarjan(int c, int p) {
    low[c] = ord[c] = ++cord;

    for (auto to : g[c]) {
        if (to != p) {
            if (!ord[to]) {
                stk.emplace_back(c, to);
                tarjan(to, c);
                low[c] = min(low[c], low[to]);

                if (low[to] >= ord[c]) {
                    int u, v, cno = ++csz;
                    vector<int> comp;
                    vector<pii> es;
                    do {
                        tie(u, v) = stk.back(); stk.pop_back();
                        comp.push_back(u); comp.push_back(v);
                        es.emplace_back(u, v);
                    } while (u != c || v != to);

                    // add the comp
                    sort(comp.begin(), comp.end());
                    comp.resize(unique(comp.begin(), comp.end()) - comp.begin());
                    for (auto x : comp) {
                        _cg[x].push_back(cno);
                        _cg[cno].push_back(x);
                    }
                    comps.push_back(Comp());
                    comps.back().ns = comp;
                    comps.back().es = es;
                    comps.back().cid = cno;
                }
            }
            else if (ord[to] < ord[c]) {
                stk.emplace_back(c, to);
                low[c] = min(low[c], ord[to]);
            }
        }
    }
}

// lca stuff
const int LG = 18;
int tb[LG][MN*2], dep[MN*2], dis[MN*2];
void dfs(int c, int p) {
    tb[0][c] = p;
    for (auto to : _cg[c]) {
        if (to != p) {
            dep[to] = dep[c] + 1;
            dfs(to, c);
        }
    }
}
void dfs2(int c, int p) {
    for (auto [to, w] : cg[c]) {
        if (to != p) {
            dis[to] = dis[c] + w;
            dfs2(to, c);
        }
    }
}

int lca(int a, int b) {
    if (a == b) return a;
    if (dep[a] > dep[b]) swap(a, b);
    int delta = dep[b]-dep[a];
    for (auto i = 0; i < LG; i++)
        if ((delta >> i) & 1)
            b = tb[i][b];
    if (a == b) return a;
    for (auto i = LG-1; i >= 0; i--) {
        if (tb[i][a] != tb[i][b]) {
            a = tb[i][a];
            b = tb[i][b];
        }
    }
    return tb[0][a];
}
int kth(int c, int k) {
    for (auto i = 0; i < LG; i++)
        if ((k >> i) & 1)
            c = tb[i][c];
    return c;
}

// get dis on cactus
int qdis(int a, int b) {
    int lcav = lca(a, b);
    if (lcav <= N) return dis[a] + dis[b] - 2*dis[lcav]; // LCA is not a component node
    else { // oh no!!!
        int preA = kth(a, dep[a]-dep[lcav]-1), preB = kth(b, dep[b]-dep[lcav]-1);
        return dis[a]-dis[preA] + dis[b]-dis[preB] + comps[lcav-N-1].qdis(preA, preB);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (auto i = 1; i <= N; i++) {
        int x; cin >> x;
        clrNodes[x].push_back(i);
    }
    for (auto i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    // do the BCC :)
    csz = N;
    tarjan(1, -1);
    // set up tree and lca stuff
    dfs(1, -1);
    for (auto i = 1; i < LG; i++) {
        for (auto j = 1; j <= N; j++) {
            int pp = tb[i-1][j];
            tb[i][j] = pp == -1 ? -1 : tb[i-1][pp];
        }
    }

    // setup component stuff
    {
        bool mark[N+1]; fill(mark, mark+N+1, false);
        vector<int> tmpg[N+1];
        for (auto &C : comps) {
            // reorder
            for (auto x : C.ns) mark[x] = true;
            for (auto [a, b] : C.es) {
                tmpg[a].push_back(b);
                tmpg[b].push_back(a);
            }
            vector<int> _ns;
            function<void(int, int, int)> dfsGetCycle = [&] (int c, int p, int st) {
                _ns.push_back(c);
                for (auto to : tmpg[c]) {
                    if (to != p && mark[to] && to != st) {
                        dfsGetCycle(to, c, st);
                        return;
                    }
                }
            };
            dfsGetCycle(C.ns[0], -1, C.ns[0]);
            for (auto x : C.ns) {
                mark[x] = false;
                tmpg[x].clear();
            }
            C.ns = _ns;

            // get root
            int mind = INF, rt = -1;
            for (auto x : C.ns) {
                if (dep[x] < mind) {
                    mind = dep[x];
                    rt = x;
                }
            }

            // init
            C.sz = C.ns.size();
            C.rt = rt;
            for (auto i = 0; i < C.sz; i++)
                C.idx[C.ns[i]] = i;
            // setup cg graph
            for (auto x : C.ns) {
                int dis = C.qdis(rt, x);
                cg[C.cid].emplace_back(x, dis);
                cg[x].emplace_back(C.cid, dis);
            }
        }
    }
    dfs2(1, -1);

    // get ans
    for (auto i = 1; i <= N; i++) {
        auto &v = clrNodes[i];
        int sz = v.size(), ans = INF;
        if (sz >= TH) { // actual brute force
            vector<int> dis(N+1, INF), clr(N+1);
            queue<int> q;
            for (auto x : v) {
                dis[x] = 0; clr[x] = x;
                q.push(x);
            }

            while (!q.empty()) {
                auto c = q.front(); q.pop();
                for (auto to : g[c]) {
                    if (dis[to] == INF) {
                        dis[to] = dis[c]+1;
                        clr[to] = clr[c];
                        q.push(to);
                    }
                    if (clr[c] != clr[to])
                        ans = min(ans, dis[c] + dis[to] + 1);
                }
            }
        }
        else if (sz >= 2) { // brute pairs
            for (auto j = 0; j < sz; j++)
                for (auto k = j+1; k < sz; k++)
                    ans = min(ans, qdis(v[j], v[k]));
        }

        cout << (ans == INF ? -1 : ans) << " \n"[i == N];
    }

    return 0;
}