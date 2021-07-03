// ./dmopc-20-contest-6-p4-land-of-the-carrot-trees-ii.yml
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
#ifdef __GNUG__
// PBDS order statistic tree
#include <ext/pb_ds/assoc_container.hpp> // Common file 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; 
template <typename T, class comp = less<T>> using os_tree = tree<T, null_type, comp, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename V, class comp = less<K>> using treemap = tree<K, V, comp, rb_tree_tag, tree_order_statistics_node_update>;
// HashSet
#include <ext/pb_ds/assoc_container.hpp>
template <typename T, class Hash> using hashset = gp_hash_table<T, null_type, Hash>;
template <typename K, typename V, class Hash> using hashmap = gp_hash_table<K, V, Hash>;
const ll RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { ll operator()(ll x) const { return x ^ RANDOM; } };
#endif
// More utilities
int SZ(string &v) { return v.length(); }
template <typename C> int SZ(C &v) { return v.size(); }
template <typename C> void UNIQUE(vector<C> &v) { sort(v.begin(), v.end()); v.resize(unique(v.begin(), v.end()) - v.begin()); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

struct Graph {
    using Edge = int; // Edge object in adjacency list (i.e. vector<int> g[MN], Edge type would be int)
    int v(Edge &e) { return e; } // Returns the adjacent node in an edge object
};
template <class Graph> struct LCA {
    using Edge = typename Graph::Edge; Graph G;
    vector<int> dep;
    vector<Edge> *g;
    vector<vector<int>> tb;
    int N, lg;
    void dfs(int c, int p) {
        tb[0][c] = p;
        for (auto to : g[c]) {
            int v = G.v(to);
            if (v != p) {
                dep[v] = dep[c] + 1;
                dfs(v, c);
            }
        }
    }
    void init(int N0, vector<Edge> *g0) {
        N = N0; g = g0;
        lg = 31 - __builtin_clz(N) + 1;
        tb.assign(lg, vector<int>(N + 1, -1)); dep.assign(N + 1, 0);
        dfs(1, -1);
        for (auto i = 1; i < lg; i++) {
            for (auto j = 1; j <= N; j++) {
                int pp = tb[i - 1][j];
                tb[i][j] = pp == -1 ? -1 : tb[i - 1][pp];
            }
        }
    }
    int lca(int a, int b) {
        if (a == b) return a;
        if (dep[a] > dep[b]) swap(a, b);
        int delta = dep[b] - dep[a];
        for (auto i = 0; i < lg; i++)
            if ((delta >> i) & 1)
                b = tb[i][b];
        if (a == b) return a;
        for (auto i = lg-1; i >= 0; i--) {
            if (tb[i][a] != tb[i][b]) {
                a = tb[i][a];
                b = tb[i][b];
            }
        }
        return tb[0][a];
    }
};
// Template is 1-indexed (by default).  Can be made 0-indexed by modifying Comp
// Default: Point increment and prefix sum query
struct Comp {
    using Data = int;
    const Data vdef = 0;
    void applyUpdate(Data &to, Data &v) { to += v; }
    int transformInd(int idx, int N) { return idx+1; }
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
        assert(x>0);
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

const int MN = 5e5 + 10;
int N, Q, ctr = 0,
    C[MN], in[MN], out[MN];
vector<int> g[MN], clr[MN];

LCA<Graph> lca;
void dfs(int c, int p) {
    in[c] = ++ctr;
    for (auto to : g[c])
        if (to != p)
            dfs(to, c);
    out[c] = ctr;
}

// count distinct query stuff
int distCnt = 0;
int subtDistPsum[MN], subtAllPsum[MN];
// void inc(int psum[MN], int l, int r, int p) { psum[l] += p; psum[r+1] -= p; }
void pathInc(int psum[MN], int c, int p) { psum[in[c]] += p; }
int rq(int psum[MN], int l, int r) { return psum[r] - psum[l-1]; }

bool ant(int top, int bot) { return in[top] <= in[bot] && out[bot] <= out[top]; }
int query(int rt, int subt) {
    if (rt == subt) return distCnt;
    else if (ant(subt, rt)) { // uh oh stinky
        int correspondingChild = *lower_bound(all(g[subt]), rt, [&] (int a, int b) { return in[a] < in[b]; });
        return distCnt - rq(subtAllPsum, in[correspondingChild], out[correspondingChild]);
    }
    else { // normal subtree
        assert(rq(subtDistPsum, in[subt], out[subt]) % 2 == 0);
        return rq(subtDistPsum, in[subt], out[subt])/2;
    }
}

// offline
int ans[MN], cur[MN];
vector<pii> qs[MN]; // (id, k)
BIT<Comp> bit;

void recalc(int c, int newRt) {
    bit.update(cur[c], -1);
    cur[c] = query(newRt, c);
    bit.update(cur[c], 1);
}

void solve(int c, int p) {
    for (auto [i, k] : qs[c])
        ans[i] = bit.query(N)-bit.query(k-1);

    for (auto to : g[c]) {
        if (to != p) {
            recalc(c, to);
            recalc(to, to);

            solve(to, c);

            recalc(c, c);
            recalc(to, c);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    for (auto i = 1; i <= N; i++)
        cin >> C[i];
    for (auto i = 0; i < N-1; i++) {
        int a, b; cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }
    for (auto i = 0; i < Q; i++) {
        int u, k; cin >> u >> k;
        qs[u].eb(i, k);
    }

    // preproc
    dfs(1, -1);
    lca.init(N, g);
    for (auto i = 1; i <= N; i++) {
        clr[C[i]].pb(i);
        sort(all(g[i]), [&] (int a, int b) { return in[a] < in[b]; });
    }
    for (auto i = 1; i <= N; i++) {
        if (!clr[i].empty()) {
            distCnt++;
            sort(all(clr[i]), [&] (int a, int b) { return in[a] < in[b]; });

            vector<int> &v = clr[i];
            int sz = SZ(clr[i]), allLca = v[0];
            for (auto x : v) allLca = lca.lca(allLca, x);
            for (auto j = 0; j < sz; j++) {
                int c = v[j], n = v[(j+1)%sz], l = lca.lca(c, n);

                pathInc(subtDistPsum, c, 1);
                pathInc(subtDistPsum, n, 1);
                pathInc(subtDistPsum, l, -2);
            }
            pathInc(subtDistPsum, allLca, 2);
            pathInc(subtAllPsum, allLca, 1);
        }
    }
    partial_sum(subtDistPsum, subtDistPsum+N+1, subtDistPsum);
    partial_sum(subtAllPsum, subtAllPsum+N+1, subtAllPsum);

    // ans
    bit.init(N+1); // supprt index==0
    for (auto i = 1; i <= N; i++) {
        cur[i] = query(1, i);
        bit.update(cur[i], 1);
    }
    solve(1, -1);
    for (auto i = 0; i < Q; i++)
        cout << (ans[i]) << '\n';

    return 0;
}