// ./knapsack-4.yml
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

ostream& operator<<(ostream& out, const pii o) {
    out << "(fs=" << o.fs << ", sn=" << o.sn << ")";
    return out;
}

// orz rpeng
const int MW = 2001*(1<<7), D = MW/2;
int N, M;
ll dp[2][MW];

void solve() {
    cin >> (N) >> (M);
    vector<pii> items;
    for (auto i = 0; i < N; i++) {
        int w, v;
        cin >> w >> v;
        items.eb(w, v);
    }
    for (auto i = 0; i < M; i++) {
        int w, v;
        cin >> w >> v;
        items.eb(-w, v);
    }
    srand(time(NULL)); random_shuffle(items.begin(), items.end());
    memset(dp, -0x3f, sizeof dp); dp[0][D] = 0;
    int c = 0, n = 1;
    for (auto item : items) {
        memset(dp[n], -0x3f, sizeof dp[n]);
        for (auto i = 0; i < MW; i++) {
            if (0 <= i + item.fs && i + item.fs < MW)
                maxa(dp[n][i + item.fs], dp[c][i] + item.sn);
            maxa(dp[n][i], dp[c][i]);
        }

        c ^= 1;
        n ^= 1;
    }
    cout << (dp[c][D]) << '\n';
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