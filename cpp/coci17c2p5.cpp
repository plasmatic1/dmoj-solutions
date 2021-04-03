// ./coci-17-contest-2-5-usmjeri.yml
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

// more stuff idk even anymore
const ll MOD = 1e9 + 7;
const int MN = 3e5 + 1, LG = 19;
int N, M,
    p[MN], dep[MN], tb[LG][MN], A[MN], B[MN];
vector<int> g[MN];

void dfs(int c) {
    for (auto to : g[c]) {
        if (to != p[c]) {
            tb[0][to] = p[to] = c;
            dep[to] = dep[c] + 1;
            dfs(to);
        }
    }
}
int lca(int a, int b) {
    if (dep[a] > dep[b]) swap(a, b);
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

// dsu
struct DSU {
    vector<int> dsu;
    DSU(int N) : dsu(N+1) { iota(dsu.begin(), dsu.end(), 0); }
    int rt(int x) { return dsu[x] == x ? x : dsu[x] = rt(dsu[x]); }
    void unite(int x, int y) {
        dsu[rt(y)] = rt(x); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M);
    for (auto i = 0; i < N-1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }

    dfs(1);
    for (auto i = 1; i < LG; i++) {
        for (auto j = 1; j <= N; j++) {
            int pp = tb[i-1][j];
            tb[i][j] = pp ? tb[i-1][pp] : 0;
        }
    }
    DSU dans(N), dcheck(2*N);

    for (auto i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        A[i] = a; B[i] = b;

        int lcav = lca(a, b), reach = dep[lcav];
        auto doMerge = [&] (int x) {
            x = dans.rt(x);
            while (p[x] && dep[p[x]] > reach) {
                dans.unite(p[x], x);
                dcheck.unite(p[x], x);
                dcheck.unite(p[x]+N, x+N);
                x = dans.rt(x);
            }
        };
        doMerge(a); doMerge(b);
    }
    for (auto i = 0; i < M; i++) {
        int a = A[i], b = B[i], lcav = lca(a, b);
        if (a != lcav && b != lcav) {
            dans.unite(a, b);
            dcheck.unite(a, b+N);
            dcheck.unite(a+N, b);
        }
    }

    ll ans = 1;
    unordered_set<int> us;
    for (auto i = 2; i <= N; i++) {
        if (dcheck.rt(i) == dcheck.rt(i+N)) {
            cout << "0\n";
            return 0;
        }
        if (!us.count(dans.rt(i))) {
            us.insert(dans.rt(i));
            ans = (ans * 2) % MOD;
        }
    }

    cout << (ans) << '\n';

    return 0;
}