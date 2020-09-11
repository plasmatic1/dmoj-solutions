// ./baltic-oi-17-p3-railway.yml
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
    int v, i;
};
struct Graph {
    using Edge = Ed; // Edge type
    int v(Edge &e) { return e.v; } // Get vertex of edge
};

const int MN = 1e5 + 1;
int N, M, K;
vector<Ed> g[MN];
HLD<Graph> lca;

int cpos = 0,
    pos[MN], preId[MN];
void dfs(int c, int p) {
    pos[c] = ++cpos;
    for (auto to : g[c]) {
        if (to.v != p) {
            preId[to.v] = to.i;
            dfs(to.v, c);
        }
    }
}

int psum[MN];
void updPath(int a, int b) {
    psum[a]++; psum[b]++;
    psum[lca.lca(a, b)] -= 2;
}

vector<int> ans;
void dfs2(int c, int p) {
    for (auto to : g[c]) {
        if (to.v != p) {
            dfs2(to.v, c);
            psum[c] += psum[to.v];
        }
    }
    // cout<<"c="<<(c)<<", "; cout<<"psum[c]="<<(psum[c])<<", "; cout<<"preId[c]="<<(preId[c])<<", "; cout << endl; // db c,psum[c],preId[c]
    if (psum[c] >= 2 * K)
        ans.pb(preId[c]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M) >> (K);
    for (auto i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb({b, i});
        g[b].pb({a, i});
    }
    lca.init(N, g);
    // assert(0);

    dfs(1, -1);
    for (auto i = 0; i < M; i++) {
        int n;
        cin >> n;
        vector<int> ns;
        for (auto j = 0; j < n; j++) {
            int x;
            cin >> x;
            ns.pb(x);
        }
        sort(all(ns), [&] (int a, int b) { return pos[a] < pos[b]; });
        for (auto j = 0; j < n; j++) {
            // cout<<"i="<<(i)<<", "; cout<<"j="<<(j)<<", "; cout<<"ns[j]="<<(ns[j])<<", "; cout<<"ns[(j+1)%n]="<<(ns[(j+1)%n])<<", "; cout << endl; // db i,j,ns[j],ns[(j+1)%n]
            updPath(ns[j], ns[(j + 1) % n]);
        }
    }
    dfs2(1, -1);

    sort(all(ans));
    cout << (SZ(ans)) << '\n';
    for (auto x : ans) cout << x << ' ';
    cout << '\n';

    return 0;
}