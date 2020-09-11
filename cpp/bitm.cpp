// ./bitmask-magic.yml
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

const int MN = 5e5 + 1, LG = 20;
int Q, L, R,
    dp[MN][LG];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (Q) >> (L) >> (R);
    
    assert(1<=Q&&Q<=4000000);
    assert(1<=L&&L<=R&&R<=500000);

    memset(dp, 0x3f, sizeof dp);
    for (auto i = MN - 1; i > 0; i--) {
        if (i >= L && i <= R)
            dp[i][0] = i;

        int hbit = 31 - __builtin_clz(i);
        for (auto j = 0; j < LG-1; j++) {
            for (auto k = 0; k <= hbit; k++) {
                if (k > 0 && k == hbit && ((i >> k) & 1) && !((i >> (k - 1)) & 1)) continue;
                int msk = (1 << k) - 1, newv = (i & msk) | ((i >> 1) & ~msk);
                mina(dp[newv][j + 1], dp[i][j]);
            }
        }
    }

    // for (auto i = 0; i <= 17; i++) {
    //     for (auto j = 0; j < 6; j++) {
    //         cout<<"i="<<(i)<<", "; cout<<"j="<<(j)<<", "; cout<<"dp[i][j]="<<(dp[i][j])<<", "; cout << endl; // db i,j,dp[i][j]
    //     }
    // }

    while (Q--) {
        int q, x;
        cin >> q >> x;
        
        assert(1<=q&&q<=500000);
        assert(1<=x&&x<=500000);

        int ans = INF;
        for (auto i = 0; i < LG; i++) {
            if (q + x >= dp[q][i]) {
                ans = i;
                break;
            }
        }
        cout << (ans == INF ? -1 : ans) << '\n';
    }

    return 0;
}