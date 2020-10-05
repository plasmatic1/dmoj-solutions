// ./good-inflation.yml
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
 * y=m(x-A)+b
 * y=mx-(mA+b)
 */

struct line {
    ll m, b;
    ll eval(ll x) { return m * x + b; }
    line shift(int x) { return {m, b - m * x}; }
};
const line def{-INF, -INF};

const int MN = 1e6 + 5, MX = MN;
#define MID int mid = (l + r) / 2, lhs = i + 1, rhs = i + (mid - l + 1) * 2;
line seg[MN * 2];
void insert(line ln, int i = 1, int l = 0, int r = 1000000) {
    MID;
    bool lb = ln.eval(l) > seg[i].eval(l), mb = ln.eval(mid) > seg[i].eval(mid);
    if (mb) swap(ln, seg[i]);
    if (l == r) return;
    else if (lb != mb) insert(ln, lhs, l, mid);
    else insert(ln, rhs, mid + 1, r);
}
ll query(ll x, int i = 1, int l = 0, int r = 1000000) {
    MID;
    ll res = seg[i].eval(x);
    if (l != r) {
        if (x <= mid) maxa(res, query(x, lhs, l, mid));
        else maxa(res, query(x, rhs, mid + 1, r));
    }
    return res;
}

int N,
    A[MN], D[MN];
ll dp[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    for (auto i = 1; i <= N; i++)
        cin >> (A[i]) >> (D[i]);

    fill(seg, seg + MN * 2, def);
    insert({0, 0});
    for (auto i = 1; i <= N+1; i++) {
        dp[i] = max(0LL, query(i)) + A[i];
        insert((line{-D[i], dp[i]}).shift(i));
    }

    cout << (dp[N+1]) << '\n';

    return 0;
}