// ./cco-17-p4-rainfall-storage.yml
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

/*
 * Consider some configuration of pillars using the i tallest pillars.  If we insert a new pillar of less than or equal height at index i of the configuration,
 * the amount of water added is equal to min(max pillar to the left of i (denote as A), max pillar to the right of i (denote as B)) - i.  Let's make some observations on this value:
 *
 * - A and/or B must be max(H[1..N])
 * - Each configuration has a set of possible values for the value of A/B that isn't the max height.  These values are the same as the prefix/suffix maxes of the configuration.
 *   For us to add another distinct prefix/suffix max, we must insert this new pillar on the leftmost or rightmost possible position, thus adding no volume.
 * 
 * - DP State: dp[i][j] = <set of possible values of A/B> for the first i tallest pillars where j is the amount of rainfall collected
 */

const int MN = 501, MH = 51, MV = 24402 + 1;
int N,
    H[MN];
ll dp[2][MV];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    for (auto i = 0; i < N; i++)
        cin >> (H[i]);
    sort(H, H + N, greater<int>());

    // do dp
    dp[0][0] = 1LL << H[1];
    for (auto i = 2; i < N; i++) {
        // init
        int c = i & 1, n = !c;
        memset(dp[n], 0, sizeof dp[n]);

        // set dp
        for (auto j = 0; j < MV; j++) {
            if (!dp[c][j]) continue;
            // insert on side
            dp[n][j] |= dp[c][j] | (1LL << H[i]);
            // insert in middle (not side)
            for (auto k = 0; k < MH; k++) {
                if ((dp[c][j] >> k) & 1) {
                    int delta = k - H[i];
                    if (j + delta < MV)
                        dp[n][j+delta] |= dp[c][j];
                }
            }
        }
    }

    // print ans
    for (auto i = 0; i < MV; i++)
        if (dp[N&1][i])
            cout << i << ' ';
    cout << '\n';

    return 0;
}