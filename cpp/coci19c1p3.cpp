// ./coci-19-contest-1-3-džumbus.yml
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

const int MN = 1001;
int N, M, Q;
vector<int> g[MN];
ll req[MN], D[MN];

bool vis[MN];
int sz[MN];
ll dp[MN][MN][2][2];
void dfs(int c) {
    vis[c] = true;
    sz[c] = 1;

    dp[c][0][0][0] = 0LL;
    dp[c][0][1][0] = D[c];
    for (int to : g[c]) {
        if (!vis[to]) {
            dfs(to);

            // Calculate tmp dp with brute force convolution
            ll tmp[sz[c] + sz[to] + 1][2][2]; memset(tmp, 0x3f, sizeof tmp);
            for (auto i = 0; i <= sz[c]; i++) { // # drunk
                for (auto j = 0; j < 2; j++) { // cur node drunk
                    for (auto k = 0; k < 2; k++) { // child drunk
                        for (auto l = 0; l <= sz[to]; l++) { // # drunk
                            for (auto m = 0; m < 2; m++) { // cur node drunk
                                for (auto n = 0; n < 2; n++) { // child drunk
                                    int nnode = i + l;
                                    if (!k && j && m) nnode++; // increment 1 for cur node
                                    if (j && m && !n) nnode++; // increment 1 for child node
                                    mina(tmp[nnode][j][k | m], dp[c][i][j][k] + dp[to][l][m][n]);
                                }
                            }
                        }
                    }
                }
            }
            // Merge tmp dp with node dp
            sz[c] += sz[to];
            for (auto i = 0; i <= sz[c]; i++)
                for (auto j = 0; j < 2; j++)
                    for (auto k = 0; k < 2; k++)
                        mina(dp[c][i][j][k], tmp[i][j][k]);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M);
    for (auto i = 1; i <= N; i++)
        cin >> (D[i]);
    for (auto i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }

    // Init DP
    int reqs = 0;
    memset(dp, 0x3f, sizeof dp);
    memset(req, 0x3f, sizeof req); req[0] = 0;

    // Calculate and merge dp
    for (auto i = 1; i <= N; i++) {
        if (vis[i]) continue;
        dfs(i);
        
        // Merge with brute-force convolution
        ll tmp[N+1]; memset(tmp, 0x3f, sizeof tmp);
        for (auto j = 0; j <= sz[i]; j++) {
            ll dpv = LLINF;
            for (auto k = 0; k < 2; k++)
                for (auto l = 0; l < 2; l++)
                    mina(dpv, dp[i][j][k][l]);
            for (auto k = 0; k <= reqs; k++)
                mina(tmp[j + k], req[k] + dpv);
        }
        reqs += sz[i];
        for (auto j = 0; j <= reqs; j++)
            mina(req[j], tmp[j]);
    }

    // Brute force queries
    cin >> (Q);
    while (Q--) {
        ll x;
        cin >> x;

        int ans = 0;
        for (auto i = 0; i <= N; i++)
            if (req[i] <= x)
                ans = i;
        cout << (ans) << '\n';
    }

    return 0;
}