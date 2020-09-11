// back-from-summer-17-p6-crowded-cities.yml
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

struct Tower {
    int i, l, w, h;
    ll p;
    bool operator<(const Tower &o) const {
        if (l == o.l) {
            if (w == o.w)
                return h < o.h;
            return w < o.w;
        }
        return l < o.l;
    }
};
istream& operator>>(istream &in, Tower &o) {
    in >> o.l >> o.w >> o.h >> o.p;
    return in;
}

const int MN = 1e5 + 1, MX = 5001;
int N,
    bit[MX][MX], par[MN];
Tower towers[MN];
ll dp[MN];

bool cmpDp(const int a, const int b) {
    return dp[a] < dp[b];
}

void upd(int x, int y, int p) {
    for (int cx = x; cx < MX; cx += cx & -cx)
        for (int cy = y; cy < MX; cy += cy & -cy)
            bit[cx][cy] = max(bit[cx][cy], p, cmpDp);
}
int query(int x, int y) {
    int res = 0;
    for (int cx = x; cx; cx -= cx & -cx)
        for (int cy = y; cy; cy -= cy & -cy)
            res = max(res, bit[cx][cy], cmpDp);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);

    // Input and sort
    for (auto i = 1; i <= N; i++) {
        cin >> (towers[i]);
        towers[i].i = i;
        if (towers[i].l < towers[i].w) swap(towers[i].l, towers[i].w);
    }
    sort(towers + 1, towers + N + 1);

    // Do DP
    for (auto i = 1; i <= N; i++) {
        par[i] = query(towers[i].w, towers[i].h);
        dp[i] = dp[par[i]] + towers[i].p;
        upd(towers[i].w, towers[i].h, i);
    }

    // Get ans (output)
    int ansId = max_element(dp + 1, dp + N + 1) - dp;
    cout << (dp[ansId]) << '\n';
    int c = ansId;
    vector<int> b;
    while (c) {
        b.pb(towers[c].i);
        c = par[c];
    }
    cout << (SZ(b)) << '\n';
    for (auto x : b)
        cout << x << ' ';
    cout << '\n';

    return 0;
}