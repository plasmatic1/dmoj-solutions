// ./mock-cco-18-contest-2-problem-1-victor-runs.yml
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

// idea: YOLO with N^3 and pray that it passes
const int MN = 305;
int N, T,
    dp[2][MN][MN][2], X[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (T);
    for (auto i = 0; i < N; i++)
        cin >> (X[i]);
    sort(X, X + N);

    // Idea: work backwards
    // dp[number of added][leftbound][rightbound][leftside or rightside]
    int ans = 0;
    for (auto i = 2; i <= N; i++) {
        int c = i&1, p = !c;
        for (int len = N; len >= 1; len--) {
            int end = N - len;
            for (auto l = 0; l <= end; l++) {
                int r = l + len - 1;
                for (int side = 0; side < 2; side++) {
                    int &ret = dp[c][l][r][side], endpos = side ? X[r] : X[l];
                    ret = INF;
                    // from dp[i-1][l-1][r][0]
                    if (l > 0) {
                        int dist = abs(endpos - X[l-1]);
                        ret = min(ret, dp[p][l-1][r][0] + dist*(i-1));
                    }
                    // from dp[i-1][l][r+1][1]
                    if (r < N-1) {
                        int dist = abs(endpos - X[r+1]);
                        ret = min(ret, dp[p][l][r+1][1] + dist*(i-1));
                    }

                    ans = max(ans, i*T - ret - i*abs(endpos));
                }
            }
        }
    }

    cout << (ans) << '\n';

    return 0;
}