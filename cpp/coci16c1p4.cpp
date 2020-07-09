// coci-16-contest-1-4-mag.yml
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
// template <typename C> int sz(C &v) { return v.size(); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

ostream& operator<<(ostream& out, const pll o) {
    out << "(first=" << o.first << ", second=" << o.second << ")";
    return out;
}

/*
You can use at most 1 node whose magic >1
*/

const int MN = 1e6 + 1;
int N,
    val[MN];
vector<int> g[MN];

// cent
bool cmpFrac(const pll &a, const pll &b) {
    return a.first * b.second < b.first * a.second;
}
pll mk(ll nu, ll de) {
    ll gv = __gcd(nu, de);
    return {nu / gv, de / gv};
}

int sz[MN];
bool block[MN];

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

pll cres{INF, 1};
int dfs(int c, int p, int up1) {
    int maxDown = 0;
    for (auto to : g[c]) {
        if (to != p && !block[to]) {
            maxDown = max(maxDown, dfs(to, c, val[c] == 1 ? up1 + 1 : 0)); } }
    cres = min(cres, mk(val[c], maxDown + up1 + 1), cmpFrac);
    return val[c] == 1 ? maxDown + 1 : 0;
}
pll decomp(int c) {
    gsz(c, -1);
    int cent = gcent(c, -1, sz[c] / 2);

    int premx = val[cent] == 1, max1 = 0, max2 = 0;
    cres = {val[cent], 1};
    for (int to : g[cent]) {
        if (!block[to]) {
            int cur = dfs(to, cent, val[cent] == 1 ? premx : 0);
            premx = max(premx, cur + 1);
            if (cur >= max1) {
                max2 = max1;
                max1 = cur;
            }
            else if (cur >= max2)
                max2 = cur;
        }
    }
    premx = val[cent] == 1;
    for (auto it = g[cent].rbegin(); it != g[cent].rend(); it++) {
        int to = *it;
        if (!block[to]) {
            premx = max(premx, dfs(to, cent, val[cent] == 1 ? premx : 0) + 1); } }

    pll res = min(cres, mk(val[cent], max1 + max2 + 1), cmpFrac);
    block[cent] = true;
    for (int to : g[cent])
        if (!block[to])
            res = min(res, decomp(to), cmpFrac);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    for (auto i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }
    bool found1 = false;
    for (auto i = 1; i <= N; i++) {
        cin >> (val[i]);
        found1 |= val[i] == 1;
    }
    if (!found1) {
        cout << (*min_element(val + 1, val + N + 1)) << "/1\n";
        return 0;
    }

    pll ans = decomp(1);
    cout << ans.first << '/' << ans.second << '\n';

    return 0;
}