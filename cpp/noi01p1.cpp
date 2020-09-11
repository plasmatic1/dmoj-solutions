// ./noi-01-p1-food-chain.yml
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
    vector<int> dsu;
    void init(int N) {
        dsu.resize(N + 1);
        iota(dsu.begin(), dsu.end(), 0);
    }
    int rt(int x) { return dsu[x] == x ? x : dsu[x] = rt(dsu[x]); }
    void merge(int x, int y) { // x -> y
        dsu[rt(x)] = rt(y); }
    bool same(int x, int y) { return rt(x) == rt(y); }
};

struct ed {
    int v, c;
};

const int MN = 5e4 + 1, MM = 1e5 + 1;
int N, M,
    clr[MN];
vector<ed> g[MN];
vector<tuple<int, int, int>> notree;
DSU dsu;

void dfs(int c, int cclr) {
    if (clr[c] != -1) return;
    clr[c] = cclr;
    for (auto to : g[c])
        dfs(to.v, (cclr + to.c + 3) % 3);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M);

    int ans = 0;

    dsu.init(N);
    for (auto i = 0; i < M; i++) {
        int t, a, b;
        cin >> t >> a >> b;

        if (a > N || b > N || (t == 2 && a == b)) ans++;
        else {
            bool same = dsu.same(a, b);
            if (same)
                notree.eb(t, a, b);
            else {
                t--;
                g[a].pb({b, t});
                g[b].pb({a, -t});
            }

            dsu.merge(a, b);
        }
    }

    memset(clr, -1, sizeof clr);
    for (auto i = 1; i <= N; i++)
        if (clr[i] == -1)
            dfs(i, 0);
    
    for (auto &tt : notree) {
        int t, a, b; tie(t, a, b) = tt;

        int expect = (clr[a] + (t - 1)) % 3;
        ans += expect != clr[b];
    }
    cout << (ans) << '\n';

    return 0;
}