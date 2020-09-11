// ./coci-19-contest-5-4-putovanje.yml
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

template <class Graph> struct HLD {
    using Edge = typename Graph::Edge; Graph G;
    int N, cpos;
    vector<Edge> *g;
    vector<int> par, dep, head, heavy, pos;
    int dfs(int c, int p) {
        par[c] = p;
        int sz = 1, mxsz = 0;
        for (auto to : g[c]) {
            int v = G.v(to);
            if (v != p) {
                dep[v] = dep[c] + 1;
                int csz = dfs(v, c); sz += csz;
                if (csz > mxsz) heavy[c] = v, mxsz = csz;
            }
        }
        return sz;
    }
    void build(int c, int chead) {
        pos[c] = ++cpos; head[c] = chead;
        if (heavy[c] != -1) build(heavy[c], chead);
        for (auto to : g[c]) {
            int v = G.v(to);
            if (v != par[c] && v != heavy[c])
                build(v, v);
        }
    }
    void init(int n0, vector<Edge> *g0) {
        N = n0; g = g0; cpos = 0;
        par.assign(N + 1, 0); dep.assign(N + 1, 0); head.assign(N + 1, 0); heavy.assign(N + 1, -1); pos.assign(N + 1, 0);
        dfs(1, -1); build(1, 1);
    }
    int lca(int a, int b) {
        while (head[a] != head[b]) {
            if (dep[head[a]] > dep[head[b]]) swap(a, b);
            b = par[head[b]];
        }
        return dep[a] < dep[b] ? a : b;
    }
};

struct Ed {
    int v; ll w1, w2;
};
ostream& operator<<(ostream& out, const Ed o) {
    out << "(v=" << o.v << ", w1=" << o.w1 << ", w2=" << o.w2 << ")";
    return out;
}
struct Graph {
    using Edge = Ed; // Edge type
    int v(Edge &e) { return e.v; } // Get vertex of edge
};

const int MN = 2e5 + 1;
int N;
vector<Ed> g[MN];
HLD<Graph> lca;

// dfs stuff
int psum[MN];

ll ans = 0;
void dfs(int c, int p, Ed pre) {
    for (auto to : g[c]) {
        if (to.v != p) {
            dfs(to.v, c, to);
            psum[c] += psum[to.v];
        }
    }
    ans += min(pre.w1 * psum[c], pre.w2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    for (auto i = 0; i < N-1; i++) {
        int a, b; ll w1, w2;
        cin >> a >> b >> w1 >> w2;
        g[a].pb({b, w1, w2});
        g[b].pb({a, w1, w2});
    }
    lca.init(N, g);

    for (auto i = 1; i < N; i++) {
        psum[i]++; psum[i + 1]++;
        psum[lca.lca(i, i + 1)] -= 2;
    }
    dfs(1, -1, {-1, 0, 0});
    cout << (ans) << '\n';

    return 0;
}