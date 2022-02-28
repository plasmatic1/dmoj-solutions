// ./tours.yml
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

const ll MOD = 1e9 + 7;
const int MN = 1e5 + 1;
int N, M, Q;
vector<int> g[MN], auxg[MN];

// tarjan
set<pii> bridge;
int cord = 0,
    ord[MN], low[MN];
void dfs1(int c, int p) {
    ord[c] = low[c] = ++cord;
    for (int to : g[c]) {
        if (to != p) {
            if (!ord[to]) {
                dfs1(to, c);
                mina(low[c], low[to]);
            }
            else
                mina(low[c], ord[to]);

            if (low[to] > ord[c]) {
                bridge.emplace(c, to);
                bridge.emplace(to, c);
            }
        }
    }
}
int comp[MN];
void dfs2(int c, int cno) {
    if (comp[c]) return;
    comp[c] = cno;
    for (int to : g[c]) {
        if (bridge.count({c, to})) continue;
        dfs2(to, cno);
    }
}

// Tree+LCA
const int LG = 17;
int tb[LG][MN], dep[MN];
bool vis[MN];
int eind = 0,
    in[MN], out[MN];
void dfs3(int c, int p) {
    vis[c] = true;
    dep[c] = p == -1 ? 0 : dep[p] + 1;
    tb[0][c] = p;
    in[c] = ++eind;
    for (int to : auxg[c])
        if (to != p)
            dfs3(to, c);
    out[c] = ++eind;
}
int lca(int a, int b) {
    if (a == b) return a;
    if (dep[b] < dep[a]) swap(a, b);
    int delta = dep[b] - dep[a];
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

// maintain delta
int delta[MN], bit[MN * 2];
void add(int x, int v) {
    for (; x <= eind; x += x & -x)
        bit[x] += v;
}
int sum(int x) {
    int sum = 0;
    for (; x; x -= x & -x)
        sum += bit[x];
    return sum;
}

// dsu
int dsu[MN];
int rt(int x) { return x == dsu[x] ? x : dsu[x] = rt(dsu[x]); }

void solve() {
    cin >> (N) >> (M) >> (Q);
    for (auto i = 1; i <= N; i++)
        dsu[i] = i;
    for (auto i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
        dsu[rt(a)] = rt(b);
    }

    // build bridge-tree
    for (auto i = 1; i <= N; i++)
        dfs1(i, -1);
    int cno = 0;
    for (auto i = 1; i <= N; i++)
        if (!comp[i])
            dfs2(i, ++cno);
    for (auto i = 1; i <= N; i++) {
        for (auto to : g[i]) {
            int a = comp[i], b = comp[to];
            if (a != b) auxg[a].pb(b);
        }
    }
    for (auto i = 1; i <= cno; i++)
        UNIQUE(auxg[i]);
    // build LCA
    for (auto i = 1; i <= cno; i++)
        if (!vis[i])
            dfs3(i, -1);
    for (auto i = 1; i < LG; i++) {
        for (auto j = 1; j <= cno; j++) {
            int pp = tb[i - 1][j];
            tb[i][j] = pp == -1 ? -1 : tb[i - 1][pp];
        }
    }

    // answer queries
    ll ans = 0;
    while (Q--) {
        char T; int a;
        cin >> T >> a;
        if (T == 'T') {
            int b, c;
            cin >> b >> c;
            if (rt(a) != rt(b)) continue;

            a = comp[a]; b = comp[b];
            add(in[a], c);
            add(in[b], c);
            int la = lca(a, b);
            add(in[la], -c);
            if (tb[0][la] != -1)
                add(in[tb[0][la]], -c);
        }
        else {
            int v = sum(out[comp[a]]) - sum(in[comp[a]] - 1) + delta[a];
            ans += v;
            delta[a] -= v;
        }
    }
    cout << (ans % MOD) << '\n';

    // reset
    // reset graph
    for (auto i = 1; i <= N; i++) g[i].clear();
    for (auto i = 1; i <= N; i++) auxg[i].clear();

    // reset tarjan
    cord = 0;
    fill(ord, ord + N + 1, 0);
    fill(low, low + N + 1, 0);
    fill(comp, comp + N + 1, 0);

    // reset tree
    fill(dep, dep + N + 1, 0);
    fill(vis, vis + N + 1, 0);
    fill(in, in + N + 1, 0);
    fill(out, out + N + 1, 0);
    for (auto i = 0; i < LG; i++)
        fill(tb[i], tb[i] + N + 1, 0);

    // bit/delta
    fill(delta, delta + N + 1, 0);
    fill(bit, bit + eind + 1, 0);

    // reset tree (val)
    eind = 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        // Input
        
        solve();

        // Reset
    }
}