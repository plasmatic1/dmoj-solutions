// ./wc-18-contest-4-s2-farming-simulator.yml
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

const int MN = 3001;
int N;
ll H,
   P[MN], W[MN], dp[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (H);
    for (auto i = 1; i <= N; i++)
        cin >> (P[i]) >> (W[i]);
    // bubblesort
    for (auto i = 1; i <= N; i++) {
        for (auto j = 1; j < N; j++) {
            if (P[j] > P[j+1]) {
                swap(P[j], P[j+1]);
                swap(W[j], W[j+1]);
            }
        }
    }

    // do dp
    for (auto i = 1; i <= N; i++) {
        dp[i] = LLINF;
        // steps:
        // go from j->i and plant everything in [j+1, i] at earliest possible time, go from i->j+1 and wait until ready, then come back
        ll maxw = W[i];
        for (auto j = i-1; j >= 0; j--) {
            ll cost = (P[i] - P[j]) + 2 * (P[i] - P[j+1]), wait = max(0LL, maxw - 2 * P[i] + 2 * P[j+1]);
            mina(dp[i], dp[j] + cost + wait);

            maxa(maxw, W[j]);
        }
    }

    ll ans = dp[N] + (H - P[N]);
    cout << (ans) << '\n';

    return 0;
}