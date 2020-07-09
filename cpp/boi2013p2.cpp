// boi-2013-p2-palindrome-free-numbers.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define pb push_back
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
template <typename C> int SZ(C &v) { return v.size(); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 18 + 1;
int digs[MN];
ll A, B,
   dp[MN][11][11][2][2]; // pos, prev, pre. prev, was 0, top (10 for "none")

ll f(ll x) {
    if (x < 0) return 0;
    string sx = to_string(x);
    int len = sx.length();
    for (auto i = 0; i < len; i++)
        digs[i] = sx[i] - '0';

    memset(dp, 0, sizeof dp);
    for (auto i = 0; i < digs[0]; i++)
        dp[0][i == 0 ? 10 : i][10][i == 0][0] = 1;
    dp[0][digs[0] == 0 ? 10 : digs[0]][10][digs[0] == 0][1] = 1;
    for (auto i = 0; i < len - 1; i++) {
        for (auto j = 0; j < 11; j++) {
            for (auto k = 0; k < 11; k++) {
                for (int was0 = 0; was0 < 2; was0++) {
                    for (int top = 0; top < 2; top++) {
                        for (int dig = 0; dig < 10; dig++) {
                            if (dig == j || dig == k || (top && dig > digs[i + 1])) continue;
                            ll &pre = dp[i][j][k][was0][top];
                            if (!pre) continue;
                            bool newTop = top && dig == digs[i + 1], new0 = was0 && dig == 0;
                            int newPre = new0 ? 10 : dig;
                            dp[i + 1][newPre][j][new0][newTop] += pre;
                        }
                    }
                }
            }
        }
    }

    ll res = 0;
    for (auto i = 0; i < 11; i++)
        for (auto j = 0; j < 11; j++)
            for (auto k = 0; k < 2; k++)
                for (auto l = 0; l < 2; l++)
                    res += dp[len - 1][i][j][k][l];
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> (A) >> (B);
    ll ans = f(B) - f(A - 1);
    cout << (ans) << '\n';

    return 0;
}