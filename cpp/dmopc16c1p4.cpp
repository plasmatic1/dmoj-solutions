// dmopc-16-contest-1-p4-tree-appraisal.yml
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
// template <typename C> int sz(C &v) { return v.size(); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 2e5 + 1;
int N, 
    val[MN], sz[MN];
bool block[MN];
vector<int> g[MN];

int gsz(int c, int p) {
    sz[c] = 1;
    for (int to : g[c])
        if (to != p && !block[to])
            sz[c] += gsz(to, c);
    return sz[c];
}
int gcent(int c, int p, int req) {
    for (int to : g[c])
        if (to != p && !block[to] && sz[to] > req)
            return gcent(to, c, req);
    return c;
}

ll asum = 0, bsum = 0, abSum = 0;
int cnt = 0;
// 0->upd, 1->query
void dfs(int c, int p, bool type, int dep, ll vsum, ll &res) {
    if (type == 0) {
        abSum += dep * vsum;
        asum += dep;
        bsum += vsum;
        cnt++;

        // Path from cent->c
        res += dep * vsum;
    }
    else {
        // (a, b), (c, d) -> (a + c + 1)(b + d)
        res += abSum + vsum * asum + dep * bsum + (dep * vsum) * cnt; // + bsum + vsum * cnt;
    }

    for (int to : g[c]) {
        if (to != p && !block[to]) {
            dfs(to, c, type, dep + 1, vsum + val[to], res);
        }
    }
}

ll decomp(int c) {
    gsz(c, -1);
    int cent = gcent(c, -1, sz[c] / 2);

    // reset vars and init res
    ll res = 0;
    asum = bsum = abSum = cnt = 0;
    for (int to : g[cent]) {
        if (!block[to]) {
            dfs(to, cent, 1, 1, val[to], res); // +1 to depth since we're joining paths
            dfs(to, cent, 0, 1, val[cent] + val[to], res);
        }
    }

    block[cent] = true;
    for (int to : g[cent]) {
        if (!block[to])
            res += decomp(to);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    for (auto i = 1; i <= N; i++)
        cin >> (val[i]);
    for (auto i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }

    ll ans = decomp(1);
    cout << (ans) << '\n';

    return 0;
}