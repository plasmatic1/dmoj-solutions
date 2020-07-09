// coci-14-contest-1-4-mafija.yml
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
    to[MN];

// Graph and vis and cycle related things
int st[MN], cnt[MN], revTo[MN];
bitset<MN> vis, cyc, instk;

// get node values
int val[MN][2], dp[2][MN];

void treeSolve(int c) {
    dp[0][c] = 1;
    for (auto i = st[c - 1]; i < st[c]; i++) {
        int p = revTo[i];
        if (!cyc[p]) {
            treeSolve(p);
            dp[0][c] += dp[1][p];
            dp[1][c] += max(dp[0][p], dp[1][p]);
        }
    }
    dp[0][c] = max(dp[0][c], dp[1][c]);
}

// do DP on cycles
int solve(int c, int dp[MN], int last) {
    if (c == last) return val[c][1];
    int &ret = dp[c];
    if (ret != -1) return ret;

    vis[c] = true;
    int alt = val[c][0] + val[to[c]][1];
    if (to[c] != last)
        alt += solve(to[to[c]], dp, last);
    ret = max(alt, val[c][1] + solve(to[c], dp, last));
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    for (auto i = 1; i <= N; i++) {
        cin >> (to[i]);
        st[to[i]]++;
    }
    partial_sum(st + 1, st + N + 1, st + 1); 
    for (auto i = 1; i <= N; i++) {
        revTo[st[to[i] - 1] + cnt[to[i]]] = i;
        cnt[to[i]]++;
    }

    // get cycle
    for (auto i = 1; i <= N; i++) {
        if (!vis[i]) {
            int c = i;
            stack<int> pre;
            while (true) {
                if (instk[c]) { // found cycle
                    cyc[c] = true;
                    while (pre.top() != c) {
                        cyc[pre.top()] = true;
                        instk[pre.top()] = false;
                        pre.pop();
                    }
                    break;
                }
                else if (vis[c]) { // rip... nevermind
                    break; }

                vis[c] = true;
                pre.push(c); instk[c] = true;
                c = to[c];
            }

            while (!pre.empty()) {
                instk[pre.top()] = false;
                pre.pop();
            }
        }
    }
    vis.reset(); // reset vis...

    // get node values
    for (auto i = 1; i <= N; i++) {
        if (cyc[i]) {
            treeSolve(i);
            for (auto j = 0; j < 2; j++)
                val[i][j] = dp[j][i];
        }
    }

    // DP on cycles
    memset(dp, -1, sizeof dp);
    int ans = 0;
    for (auto i = 1; i <= N; i++) {
        if (!vis[i] && cyc[i]) {
            int lst = i;
            while (to[lst] != i) lst = to[lst];
            int curAns = max(solve(i, dp[0], lst), solve(to[i], dp[1], i));
            ans += curAns;
        }
    }

    cout << (ans) << '\n';

    return 0;
}