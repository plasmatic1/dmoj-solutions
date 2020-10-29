// ./dmopc-20-contest-1-p5-victor-takes-over-canada.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define fs first
#define sn second
#define pb push_back
#define eb emplace_back
#define mpr make_pair
#define mtp make_tuple
#define all(x) (x).begin(), (x).end()
// Basic type definitions
using ll = long long; using ull = unsigned long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<long long, long long>;
// PBDS order statistic tree
#include <ext/pb_ds/assoc_container.hpp> // Common file 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; 
template <typename T, class comp = less<T>> using os_tree = tree<T, null_type, comp, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename V, class comp = less<K>> using treemap = tree<K, V, comp, rb_tree_tag, tree_order_statistics_node_update>;
// HashSet
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
const ll RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { ll operator()(ll x) const { return x ^ RANDOM; } };
template <typename T, class Hash> using hashset = gp_hash_table<T, null_type, Hash>;
template <typename K, typename V, class Hash> using hashmap = gp_hash_table<K, V, Hash>;
// More utilities
int SZ(string &v) { return v.length(); }
template <typename C> int SZ(C &v) { return v.size(); }
template <typename C> void UNIQUE(vector<C> &v) { sort(v.begin(), v.end()); v.resize(unique(v.begin(), v.end()) - v.begin()); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

// Template is 1-indexed (by default).  Can be made 0-indexed by modifying Comp
// Default: Point increment and prefix sum query
struct Comp {
    using Data = int;
    const Data vdef = 0;
    void applyUpdate(Data &to, Data &v) { to += v; }
    int transformInd(int idx, int N) { return idx; }
};
template <typename Comp> struct BIT {
    using Data = typename Comp::Data; Comp C;
    int N; vector<Data> bit;
    void init(int n0) {
        N = n0;
        bit.assign(N + 1, C.vdef);
    }
    void update(int x, Data v) {
        x = C.transformInd(x, N);
        for (; x <= N; x += x & -x)
            C.applyUpdate(bit[x], v);
    }
    Data query(int x) {
        x = C.transformInd(x, N);
        Data res = C.vdef;
        for (; x; x -= x & -x)
            C.applyUpdate(res, bit[x]);
        return res;
    }
};

ostream& operator<<(ostream& out, const pii o) {
    out << "(fs=" << o.fs << ", sn=" << o.sn << ")";
    return out;
}
ostream& operator<<(ostream& out, const pii* o) {
    if (!o) {
        out << "*(NULL)";
    }
    else out << "*(fs=" << o->fs << ", sn=" << o->sn << ")";
    return out;
}

const int MN = 5e5 + 1;
int N, K, Q,
    in[MN], out[MN];
vector<int> g[MN];

// hld
int cpos = 0, epos = 0,
    par[MN], head[MN], heavy[MN], pos[MN], dep[MN];
int dfs(int c, int p) {
    par[c] = p; heavy[c] = -1; 
    in[c] = ++epos;
    int csz = 1, best = -1;
    for (int to : g[c]) {
        if (to != p) {
            dep[to] = dep[c] + 1;
            int chsz = dfs(to, c); csz += chsz;
            if (chsz > best) { best = chsz; heavy[c] = to; }
        }
    }
    out[c] = epos;
    return csz;
}
void build(int c, int chead) {
    head[c] = chead; pos[c] = ++cpos;
    if (heavy[c] != -1) build(heavy[c], chead);
    for (int to : g[c]) {
        if (to != par[c] && to != heavy[c])
            build(to, to);
    }
}
int lca(int a, int b) {
    while (head[a] != head[b]) {
        if (dep[head[a]] > dep[head[b]]) swap(a, b);
        b = par[head[b]];
    }
    return dep[a] < dep[b] ? a : b;
}

BIT<Comp> bit;
set<pii> et[MN];
int ass[MN];

// updates path u->v (EDGES), skips lca(u, v)
void pathu(int u, int v, int d) {
    bit.update(in[u], d);
    bit.update(in[v], d);
    int lv = lca(u, v);
    bit.update(in[lv], -2 * d);
}
int nodeq(int u) {
    return bit.query(out[u]) - bit.query(in[u] - 1);
}

void change(int c, int u, int delta) {
    if (u == 1) return;

    auto pp = mpr(in[u], u);
    auto &tour = et[c];

    auto nxt = tour.upper_bound(pp), pre = tour.lower_bound(pp);
    if (nxt == tour.end()) nxt = tour.begin();
    if (pre == tour.begin()) pre = --tour.end();
    else pre--;

    pathu(pre->sn, nxt->sn, -delta);
    pathu(pre->sn, u, delta);
    pathu(u, nxt->sn, delta);
}

int distGuards = 0,
    gcnt[MN];
void incg(int c) {
    if (gcnt[c] == 0) distGuards++;
    gcnt[c]++;
}
void decg(int c) {
    gcnt[c]--;
    if (gcnt[c] == 0) distGuards--;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (K) >> (Q);
    for (auto i = 1; i <= N; i++)
        cin >> (ass[i]);
    for (auto i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }

    dfs(1, -1);
    build(1, 1);
    bit.init(N);

    for (auto i = 1; i <= K; i++)
        et[i].emplace(in[1], 1);
    for (auto i = 1; i <= N; i++) {
        change(ass[i], i, 1);
        if (i != 1) et[ass[i]].emplace(in[i], i);
        incg(ass[i]);
    }

    while (Q--) {
        int T;
        cin >> T;
        if (T == 1) {
            int c, k;
            cin >> c >> k; // c IS CITY, k is GUARD GROUP

            change(ass[c], c, -1);
            if (c != 1) et[ass[c]].erase(mpr(in[c], c));
            decg(ass[c]);
            ass[c] = k;

            change(k, c, 1);
            if (c != 1) et[k].emplace(in[c], c);
            incg(k);
        }
        else {
            int u;
            cin >> u;

            if (u == 1)
                cout << (distGuards) << '\n';
            else {
                int ans = nodeq(u) / 2;
                cout << (ans) << '\n';
            }
        }
    }

    return 0;
}