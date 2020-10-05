// ./noi-02-p3-the-greedy-kuzuryū.yml
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

const int MN = 301;
int N, M, K,
    dp[MN][MN][2]; // dp[subtree][number of type 1 selected][root node is type 1 or not]
vector<pii> g[MN];

void dfs(int c, int p) {
    memset(dp[c], 0x3f, sizeof dp[c]);
    dp[c][1][0] = dp[c][0][1] = 0;

    for (auto to : g[c]) {
        if (to.fs != p) {
            dfs(to.fs, c);

            int tmp[MN][2]; memset(tmp, 0x3f, sizeof tmp);
            for (auto i = 0; i <= K; i++) {
                for (auto j = 0; j < 2; j++) {
                    for (auto k = 0; k <= K; k++) {
                        if (i + k > K) continue;
                        for (auto l = 0; l < 2; l++) {
                            int add = (j == l && (j == 0 || M == 2)) * to.sn;
                            mina(tmp[i + k][j], dp[c][i][j] + dp[to.fs][k][l] + add);
                        }
                    }
                }
            }

            for (auto i = 0; i <= K; i++)
                for (auto j = 0; j < 2; j++)
                    dp[c][i][j] = tmp[i][j];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M) >> (K);
    if (K + M - 1 > N) {
        cout << (-1) << '\n';
        return 0;
    }

    for (auto i = 1; i < N; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].eb(b, c);
        g[b].eb(a, c);
    }

    dfs(1, -1);
    cout << (dp[1][K][0]) << '\n';

    return 0;
}