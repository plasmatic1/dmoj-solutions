// ./apio-14-p3-beads-and-wires.yml
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

Procedure:
Select any node and two of its incident edges, those edges can become blue edges.  Each node and edge can be selected at most once.

Some additional constraints also apply:
- A root must be chosen (any root)
- All pairs of edge selected must have depths go in monotonous order (WLOG assume a<b<c, dep[a]=dep[b]-1=dep[c]-2)

*/

struct ed {
    int v, w;
};

const int MN = 2e5 + 1;
int N,
    dp[MN][2], dp2[MN][2], parw[MN], delta[MN];
vector<ed> g[MN];

// down part
void dfs(int c, int p) {
    int maxv = INT_MIN;
    for (auto to : g[c]) {
        if (to.v != p) {
            dfs(to.v, c);
            int base = max(dp[to.v][0], dp[to.v][1] + to.w);
            dp[c][0] += base;
            dp[c][1] += base;
            maxa(maxv, dp[to.v][0] + to.w - base);
        }
    }
    if (maxv == INT_MIN) dp[c][1] = INT_MIN;
    else dp[c][1] += maxv;
}

// "up" part of up/down
void dfs2(int c, int p) {
    int acc, maxv;
    if (c > 1) {
        int base = max(dp2[c][0], dp2[c][1] + parw[c]);
        acc = base;
        maxv = dp2[c][0] + parw[c] - base; // use dp2[par]
    }
    else {
        acc = 0;
        maxv = INT_MIN;
    }
    
    // sweep forward
    for (auto to : g[c]) {
        if (to.v != p) {
            parw[to.v] = to.w;

            int base = max(dp[to.v][0], dp[to.v][1] + to.w); // dp (pull)
            dp2[to.v][0] += acc; // dp2 (push)
            dp2[to.v][1] += acc; // dp2 (push)
            maxa(delta[to.v], maxv); // dp2 (push)

            maxa(maxv, dp[to.v][0] + to.w - base); // dp (pull)
            acc += base;
        }
    }

    // sweep in reverse
    acc = 0; maxv = INT_MIN;
    for (auto it = g[c].rbegin(); it != g[c].rend(); it++) {
        auto to = *it;
        if (to.v != p) {
            parw[to.v] = to.w;

            int base = max(dp[to.v][0], dp[to.v][1] + to.w); // dp (pull)
            dp2[to.v][0] += acc; // dp2 (push)
            dp2[to.v][1] += acc; // dp2 (push)
            maxa(delta[to.v], maxv); // dp2 (push)

            maxa(maxv, dp[to.v][0] + to.w - base); // dp (pull)
            acc += base;
        }
    }

    // dfs to children
    for (auto to : g[c]) {
        if (to.v != p) {
            // finalize dp2[to.v][1]
            if (delta[to.v] == INT_MIN) dp2[to.v][1] = INT_MIN; // dp2 (push)
            else dp2[to.v][1] += delta[to.v]; // dp2 (push)

            // continue
            dfs2(to.v, c);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> (N);
    for (auto i = 1; i < N; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        g[a].pb({b, w});
        g[b].pb({a, w});
    }

    // init arrays
    fill(delta, delta + N + 1, INT_MIN);
    dp2[1][1] = INT_MIN;

    // do dfs
    dfs(1, -1);
    dfs2(1, -1);

    // merge to compute answer
    int ans = 0;
    for (auto i = 1; i <= N; i++)
        maxa(ans, dp[i][0] + (i > 1 ? max(dp2[i][0], dp2[i][1] + parw[i]) : dp2[i][0]));
    cout << (ans) << '\n';

    return 0;
}