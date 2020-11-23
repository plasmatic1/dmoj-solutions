// ./james-xor-update.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define fs first
#define sn second
#define pb push_back
#define eb emplace_back
#define mpr make_pair
#define mtp make_tuple
#define even(x) (x).begin(), (x).end()
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

const int MN = 2e5 + 1;
int N, Q;
ll val[MN];
vector<int> g[MN];

int par[MN], dep[MN], head[MN], pos[MN], heavy[MN], cpos = 0;
int dfs(int c, int p) {
    par[c] = p;
    int sz = 1, hsz = -1;
    for (int to : g[c]) {
        if (to != p) {
            dep[to] = dep[c] + 1;
            int csz = dfs(to, c); sz += csz;
            if (csz > hsz) {
                heavy[c] = to;
                hsz = csz;
            }
        }
    }
    return sz;
}
void build(int c, int chead) {
    head[c] = chead;
    pos[c] = ++cpos;
    if (heavy[c]) build(heavy[c], chead);
    for (int to : g[c]) {
        if (to != par[c] && to != heavy[c])
            build(to, to);
    }
}
int lca(int u, int v) {
    while (head[u] != head[v]) {
        if (dep[head[u]] > dep[head[v]]) swap(u, v);
        v = par[head[v]];
    }
    return dep[u] < dep[v] ? u : v;
}
int dis(int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }

ll psum[MN][2];
void collect(int c) {
    for (int to : g[c]) {
        if (to != par[c]) {
            collect(to);
            for (auto i = 0; i < 2; i++)
                psum[c][i] ^= psum[to][i];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (Q);
    for (auto i = 1; i <= N; i++)
        cin >> (val[i]);
    for (auto i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }

    dfs(1, -1);
    build(1, 1);

    while (Q--) {
        int a, b; ll x;
        cin >> a >> b >> x;

        int l = lca(a, b), ap = dep[a] & 1, bp = dep[b] & 1, lp = dep[l] & 1;
        psum[a][ap] ^= x;
        if (bp == ap) psum[b][ap] ^= x;
        else if (par[b] != -1) psum[par[b]][ap] ^= x;

        if (lp == ap) { // lca is odd index
            psum[l][ap] ^= x;
            if (par[l] != -1) psum[par[l]][ap] ^= x;
        }
        // if lca is even index, do nothing
    }

    collect(1);
    for (auto i = 1; i <= N; i++) {
        cout << (val[i] ^ psum[i][dep[i] & 1]) << ' ';
    }
    cout << '\n';

    return 0;
}