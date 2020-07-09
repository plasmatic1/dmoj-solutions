// back-to-school-19-unstable-books.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define pb push_back
#define fs first
#define sn second
#define mpr make_pair
#define mtp make_tuple
#define all(x) (x).begin(), (x).end()
// Basic type definitions
using ll = long long; using ull = unsigned long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<long, long>;
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
template <typename C> int sz(C &v) { return v.size(); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 5e5 + 1;
int N, 
    H[MN], dp[MN][2][2][2]; // left side prev. increasing, right side prev. increasing, prev. numbers were swapped
// Dp is done from right and left ends at the same time

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    for (auto i = 1; i <= N; i++)
        cin >> (H[i]);

    memset(dp, 0x3f, sizeof dp);
    memset(dp[1], 0, sizeof dp[1]);
    int half = (N + 1) / 2; // Ceildiv
    for (auto i = 1; i < half; i++) {
        for (auto j = 0; j < 2; j++) {
            for (auto k = 0; k < 2; k++) {
                for (auto l = 0; l < 2; l++) {
                    int prevA = H[i], prevB = H[N - i + 1];
                    if (l) swap(prevA, prevB);
                    for (auto m = 0; m < 2; m++) {
                        int curA = H[i + 1], curB = H[N - i];
                        if (m) swap(curA, curB);
                        bool leftInc = curA > prevA, rightInc = curB > prevB;
                        int &nxtDp = dp[i + 1][leftInc][rightInc][m];
                        nxtDp = min(nxtDp, dp[i][j][k][l] + (leftInc != j) + (rightInc != k));
                    }
                }
            }
        }
    }

    // Separate odd and even cases
    if (N % 2) {
        int ans = INF;
        for (auto i = 0; i < 2; i++) {
            for (auto j = 0; j < 2; j++) {
                for (auto k = 0; k < 2; k++) {
                    ans = min(ans, dp[half][i][j][k] + (i == j) + 1); } } }
        cout << (ans) << '\n';
    }
    else {
        int ans = INF;
        for (auto i = 0; i < 2; i++) {
            for (auto j = 0; j < 2; j++) {
                for (auto k = 0; k < 2; k++) {
                    int curA = H[half], curB = H[half + 1];
                    if (k) swap(curA, curB);
                    bool leftInc = i, rightInc = !j, curInc = curA < curB;
                    ans = min(ans, dp[half][i][j][k] + (leftInc != curInc) + (rightInc != curInc) + 1);
                }
            }
        }
        cout << (ans) << '\n';
    }

    return 0;
}