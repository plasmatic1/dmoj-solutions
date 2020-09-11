// ./apio-18-p3-duathlon.yml
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

struct DSU {
    vector<int> dsu, sz;
    void init(int N) {
        dsu.resize(N);
        iota(dsu.begin(), dsu.end(), 0);
        sz.assign(N, 1);
    }
    int rt(int x) { return dsu[x] == x ? x : dsu[x] = rt(dsu[x]); }
    void merge(int x, int y) { // x -> y
        x = rt(x); y = rt(y);
        if (x == y) return;
        sz[y] += sz[x];
        dsu[x] = y;
    }
    int gsz(int x) { return sz[rt(x)]; }
};

const int MN = 1e5 + 1, MNODE = MN * 3;
int N, M;
vector<int> g[MN], auxg[MNODE];

int nodeCtr, cord = 0,
    low[MN], ord[MN];
vector<pii> stk;

void dfs(int c, int p) {
    low[c] = ord[c] = ++cord;
    for (int to : g[c]) {
        if (to != p) {
            if (!ord[to]) {
                stk.eb(c, to);
                dfs(to, c);
                mina(low[c], low[to]);
                if (low[to] >= ord[c]) {
                    int compNo = ++nodeCtr, u, v;
                    do {
                        u = stk.back().fs; v = stk.back().sn;
                        stk.pop_back();
                        auxg[v].pb(compNo); auxg[compNo].pb(v);
                    } while (u != c || v != to);
                    auxg[c].pb(compNo); auxg[compNo].pb(c);
                }
            }
            else if (ord[to] < ord[c]) {
                stk.eb(c, to);
                mina(low[c], ord[to]);
            }
        }
    }
}

/*
Biconnected component patterns:

Case 1: A -> B -> C
Case 2: A -> A -> B
Case 3: B -> A -> A
Case 4: A -> A -> A

A -> B -> A // Note that this case is impossible
*/

ll sz[MNODE];
int par[MNODE];
bool vis[MNODE];
int dfs2(int c, int p) {
    sz[c] = c <= N;
    par[c] = p;
    assert(!vis[c]);
    vis[c] = true;
    for (int to : auxg[c]) {
        if (to != p)
            sz[c] += dfs2(to, c);
    }
    return sz[c];
}

DSU dsu;

ll P3(ll x) { return x * (x - 1) * (x - 2); }
ll P2(ll x) { return x * (x - 1); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M);
    for (auto i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }

    // Build BCC tree
    nodeCtr = N;
    for (auto i = 1; i <= N; i++)
        if (!ord[i])
            dfs(i, -1);
    dsu.init(nodeCtr+1);
    fill(dsu.sz.begin() + N+1, dsu.sz.end(), 0);
    for (auto i = 1; i <= nodeCtr; i++) {
        UNIQUE(auxg[i]);
        for (int to : auxg[i])
            dsu.merge(i, to);
    }

    // DFS tree for DP
    for (auto i = 1; i <= nodeCtr; i++)
        if (!vis[i])
            dfs2(i, -1);

    // Get ans (tree case)
    ll ans = 0;
    for (auto i = 1; i <= N; i++) { 
        ll nn = dsu.gsz(i), parSz = nn - sz[i];
        for (auto to : auxg[i])
            if (to != par[i])
                ans += (nn - 1 - sz[to]) * sz[to];
        if (par[i] != -1)
            ans += (nn - 1 - parSz) * parSz;
    }

    // Get ans (non tree case)
    for (auto i = N+1; i <= nodeCtr; i++) {
        ll nn = dsu.gsz(i);
        vector<ll> sizes;
        for (auto to : auxg[i]) {
            if (to != par[i]) {
                sizes.pb(sz[to]);
            }
        }
        if (par[i] != -1)
            sizes.pb(nn - sz[i]);

        int sz = SZ(auxg[i]); assert(sz == SZ(sizes));

        // Pairwise sum and things
        ll csum = 0, cadd = 0;
        for (auto i = 0; i < sz; i++) {
            cadd += sizes[i] * csum;
            csum += sizes[i];
        }
        ans += cadd * (sz - 2) * 2;
    }

    cout << (ans) << '\n';

    return 0;
}