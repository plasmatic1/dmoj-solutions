// ./ioi-18-p3-werewolf.yml
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

const int MN = 2e5 + 1, LG = 18;
int N, M, Q;
vector<int> g[MN];

// dsu
int dsu[MN];
void poopoohead() { iota(dsu, dsu + N + 1, 0); }
int rt(int x) { return dsu[x] == x ? x : dsu[x] = rt(dsu[x]); }
void unite(int x, int y) { dsu[rt(y)] = rt(x); } // Unite y into x

// tree ds
struct tree {
    vector<int> tour, g[MN];
    int in[MN], out[MN], cpos;
    void addEdge(int a, int b) {
        g[a].pb(b);
        g[b].pb(a);
    }
    // I have lost myself
    int tb[LG][MN];
    void dfs(int c, int p) {
        in[c] = ++cpos;
        tour.pb(c);
        tb[0][c] = p;
        for (auto to : g[c])
            if (to != p)
                dfs(to, c);
        out[c] = cpos; // euler tour but haha
    }
    void init(int st) {
        tour.pb(-1);
        cpos = 0;
        dfs(st, -1);
        for (auto i = 1; i < LG; i++)
            for (auto j = 0; j < N; j++)
                tb[i][j] = tb[i-1][j] == -1 ? -1 : tb[i-1][tb[i-1][j]];
    }
    int query(int n, function<bool(int)> check) {
        for (auto i = LG-1; i >= 0; i--)
            if (tb[i][n] != -1 && check(tb[i][n]))
                n = tb[i][n];
        return n;
    }

    void poopoohead() {
        for (auto i = 0; i < N; i++)
            for (auto j : g[i])
                if (i<j)
                    cout << i << ' ' << j << '\n';
    }
} humant, wolft;

// segtree and offline
struct Query {
    int i, a, b, c, d;
    bool operator<(const Query &o) const {
        return d < o.d;
    }
};
const int SN = 262144;
int seg[SN*2]; // max segtree
void update(int i, int v) {
    seg[i += SN] = v;
    for (i >>= 1; i; i >>= 1)
        seg[i] = max(seg[i*2], seg[i*2+1]);
}
int query(int l, int r) {
    int res = 0;
    for (l += SN, r += SN; l <= r; l >>= 1, r >>= 1) {
        if (l & 1) maxa(res, seg[l]), l++;
        if (!(r & 1)) maxa(res, seg[r]), r--;
    }
    return res;
}

std::vector<int> check_validity(int N_, std::vector<int> X, std::vector<int> Y, std::vector<int> S, std::vector<int> E, std::vector<int> L, std::vector<int> R) {
    N = N_;
    M = SZ(X);
    Q = SZ(S);

    // build human and wolf trees
    vector<pair<int, int>> maxed, mined;
    for (auto i = 0; i < M; i++) {
        int a = X[i], b = Y[i];
        if (a < b) swap(a, b);
        maxed.eb(a, b);
        mined.eb(b, a);
    }
    sort(all(maxed));
    sort(all(mined), greater<pii>());
    poopoohead();
    for (auto e : maxed) {
        assert(e.fs > e.sn);
        if (rt(e.fs) != rt(e.sn)) {
            wolft.addEdge(e.fs, rt(e.sn));
            unite(e.fs, e.sn);
        }
    }
    poopoohead(); // :)
    for (auto e : mined) {
        assert(e.fs < e.sn);
        if (rt(e.fs) != rt(e.sn)) {
            humant.addEdge(e.fs, rt(e.sn));
            unite(e.fs, e.sn);
        }
    }

    // init binary lifting and euler tour
    humant.init(0);
    wolft.init(N-1);

    // get queries
    vector<Query> qs;
    for (auto i = 0; i < Q; i++) {
        int snode = humant.query(S[i], [&] (int n) { return n >= L[i]; }),
            enode = wolft.query(E[i], [&] (int n) { return n <= R[i]; });
        qs.pb({i, humant.in[snode], humant.out[snode], wolft.in[enode], wolft.out[enode]});
    }

    // answer queries offline
    sort(all(qs));
    int dptr = 1;
    vector<int> ans(Q);
    for (auto &q : qs) {
        while (dptr <= q.d) {
            int nd = wolft.tour[dptr];
            update(humant.in[nd], dptr);
            dptr++;
        }
        ans[q.i] = query(q.a, q.b) >= q.c;
    }

    return ans;
}

#ifdef LOCAL
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M, Q;
    cin >> N >> M >> Q;
    vector<int> X(M), Y(M);
    for (auto i = 0; i < M; i++)
        cin >> (X[i]) >> (Y[i]);
    vector<int> S(Q), E(Q), L(Q), R(Q);
    for (auto i = 0; i < Q; i++)
        cin >> (S[i]) >> (E[i]) >> (L[i]) >> (R[i]);
    for (auto a : check_validity(N, X, Y, S, E, L, R))
        cout << (a) << '\n';
    return 0;
}
#endif