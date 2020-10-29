// ./apio-15-p1-bali-sculptures.yml
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

const int MN = 2001, SMALL = 101, LG = 42;
int N, A, B;
ll val[MN], psum[MN], dp1[SMALL][SMALL], dp2[MN];
ll cost(int l, int r) { return psum[r] - psum[l - 1]; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (A) >> (B);
    for (auto i = 1; i <= N; i++)
        cin >> (val[i]);
    partial_sum(val, val + N + 1, psum);

    ll ans = 0, msk = 0;
    for (auto i = LG-1; i >= 0; i--) {
        msk |= 1LL << i;
        if (A == 1) {
            memset(dp2, 0x3f, sizeof dp2);
            dp2[0] = 0;
            for (auto j = 1; j <= N; j++) {
                for (auto k = 0; k < j; k++) {
                    if ((ans | ((psum[j] - psum[k]) & msk)) == ans)
                        mina(dp2[j], dp2[k] + 1);
                }
            }
            if (dp2[N] > B) ans |= 1LL << i;
        }
        else {
            memset(dp1, 0, sizeof dp1);
            dp1[0][0] = true;
            for (auto j = 1; j <= N; j++) {
                for (auto k = 1; k <= j; k++) {
                    for (auto l = 0; l < j; l++) {
                        if ((ans | ((psum[j] - psum[l]) & msk)) == ans)
                            dp1[j][k] |= dp1[l][k - 1];
                    }
                }
            }

            bool good = false;
            for (auto j = A; j <= B; j++) good |= dp1[N][j];
            if (!good) ans |= 1LL << i;
        }
    }

    cout << (ans) << '\n';

    return 0;
}