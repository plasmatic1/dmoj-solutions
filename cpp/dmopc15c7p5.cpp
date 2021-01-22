// ./dmopc-15-contest-7-p5-ariadnes-thread.yml
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

const int MN = 1e5 + 1, LG = 17;
int N, Q;
vector<int> g[MN];

int ctr = 0, 
    fst[MN], sz[MN], tb[LG][MN], dep[MN];
void dfs(int c, int p) {
    fst[c] = ++ctr;
    tb[0][c] = p;
    sz[c] = 1;
    for (auto to : g[c]) {
        if (to != p) {
            dep[to] = dep[c] + 1;
            dfs(to, c);
            sz[c] += sz[to];
            ++ctr;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    for (auto i = 1; i <= N; i++) {
        int x;
        cin >> x;
        for (auto j = 0; j < x; j++) {
            int c;
            cin >> c;
            g[i].pb(c);
        }
    }
    dfs(1, -1);

    for (auto i = 1; i < LG; i++) {
        for (auto j = 1; j <= N; j++) {
            int pp = tb[i-1][j];
            tb[i][j] = pp == -1 ? -1 : tb[i-1][pp];
        }
    }
    auto lca = [&] (int u, int v) {
        if (dep[u] > dep[v]) swap(u, v);
        int delta = dep[v] - dep[u];
        for (auto i = 0; i < LG; i++)
            if ((delta >> i) & 1)
                v = tb[i][v];
        if (u == v) return u;
        for (auto i = LG-1; i >= 0; i--) {
            if (tb[i][u] != tb[i][v]) {
                u = tb[i][u];
                v = tb[i][v];
            }
        }
        return tb[0][u];
    };
    auto kth = [&] (int u, int k) {
        for (auto i = 0; i < LG; i++)
            if ((k >> i) & 1)
                u = tb[i][u];
        return u;
    };

    cin >> (Q);
    while (Q--) {
        int u, v;
        cin >> u >> v;

        int ant = lca(u, v);
        if (u == ant)
            cout << (fst[v]-fst[u]) << '\n';
        else if (v == ant) {
            int pre = kth(u, dep[u] - dep[ant] - 1);
            cout << (2 * sz[pre] - (dep[u] - dep[ant])) << '\n';
        }
        else {
            int ans = (fst[v] - fst[ant]) - (dep[u] - dep[ant]), pre = kth(u, dep[u] - dep[ant] - 1);
            if (fst[v] < fst[u]) ans += 2 * sz[pre];
            cout << (ans) << '\n';
        }
    }

    return 0;
}