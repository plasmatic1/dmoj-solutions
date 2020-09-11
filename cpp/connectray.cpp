// ./rays-tricky-connectivity.yml
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

const int MN = 4e5 + 1;
int N, M, Q;
vector<int> g[MN];
bool vis[MN];
void dfs(int c) {
    if (vis[c]) return;
    vis[c] = true;
    for (int to : g[c]) dfs(to);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M) >> (Q);
    for (auto i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
    }
    assert(1<=N&&N<=400000);
    assert(0<=M&&M<=400000);
    assert(0<=Q&&Q<=400000);
    
    dfs(1);
    int aq=0;
    while (Q--) {
        char T;
        cin >> T;
        if (T == '+') {
            int a, b;
            cin >> a >> b;
            assert(1<=a&&a<=N);
            assert(1<=b&&b<=N);
            g[a].pb(b);
            if (vis[a]) dfs(b);
        }
        else {aq++;
            int x;
            cin >> x;
            assert(1<=x&&x<=N);
            cout << (vis[x] ? "YES" : "NO") << '\n';
        }
    }
    if (N==400000&&M==399999) {
        assert(aq==100000);
    }

    return 0;
}