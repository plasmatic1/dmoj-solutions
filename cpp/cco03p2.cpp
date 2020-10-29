// ./cco-03-p2-concentration-cards.yml
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

// max. no of factors of a number <=1e9 is <1440
// DIV(1,102,701,600) = 1440
const pii BAD = mpr(-1, -1);
int N, W, H;

pii compute(int n, int same) {
    if (n == 0) return mpr(same, 0);
    int area = n * W * H, other = area / same, w = W, h = H;
    for (auto i = 0; i < 2; i++) {
        if (same % w == 0 && other % h == 0)
            return mpr(same, other);
        swap(w, h);
    }
    return BAD;
}

int computePerim(pii &p) {
    return 2 * p.fs + 2 * p.sn;
}

void solve() {
    cin >> (N) >> (W) >> (H);

    int area = N * W * H;
    vector<int> fct;
    for (int i = 1; i * i <= area; i++) {
        if (area % i == 0) {
            fct.pb(i);
            if (i * i != area) fct.pb(area / i);
        }
    }

    int ans = INT_MAX;
    for (auto i = 0; i <= N; i++) {
        for (auto &f : fct) {
            auto r1 = compute(i, f), r2 = compute(N - i, f);
            if (r1 == BAD || r2 == BAD) continue;
            int perim = computePerim(r1) + computePerim(r2) - 2 * f;
            mina(ans, perim);
        }
    }
    cout << (ans) << '\n';
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