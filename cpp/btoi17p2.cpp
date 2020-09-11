// ./baltic-oi-17-p2-toll.yml
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
Solution: segtree of matrices using tropical sets instead of add/mul
*/

struct Ed {
    int v, w;
};

using Mat = array<array<int, 5>, 5>;
using Vec = array<int, 5>;

const int MN = 50001;
int N, M, K, Q;
vector<Ed> g[MN];

// Matrix ops
void init(Mat &res) {
    for (auto i = 0; i < K; i++)
        for (auto j = 0; j < K; j++)
            res[i][j] = INF;
}
void initIdentity(Mat &res) {
    init(res);
    for (auto i = 0; i < K; i++)
        res[i][i] = 0;
}
void mul(Mat &f, Mat &g, Mat &res) {
    init(res);
    for (auto i = 0; i < K; i++)
        for (auto j = 0; j < K; j++)
            for (auto k = 0; k < K; k++)
                mina(res[i][j], f[i][k] + g[k][j]);
}

// Segtree ops
int sz;
#define MID int mid = (l + r) / 2, lhs = i + 1, rhs = i + (mid - l + 1) * 2
Mat seg[MN * 2];
void build(int i = 1, int l = 0, int r = sz - 1) {
    if (l == r) {
        init(seg[i]);
        for (auto j = l*K; j < l*K+K; j++) {
            for (auto to : g[j])
                mina(seg[i][to.v % K][j % K], to.w);
        }
        return;
    }
    MID;
    build(lhs, l, mid); build(rhs, mid + 1, r);
    mul(seg[rhs], seg[lhs], seg[i]);
}
Mat query(int ql, int qr, int i = 1, int l = 0, int r = sz - 1) {
    if (l > qr || r < ql) {
        Mat res; initIdentity(res);
        return res;
    }
    if (l >= ql && r <= qr) return seg[i];
    MID;
    Mat res, ll = query(ql, qr, lhs, l, mid), rr = query(ql, qr, rhs, mid + 1, r); mul(rr, ll, res);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (K) >> (N) >> (M) >> (Q);
    for (auto i = 0; i < M; i++) {
        int a, b, t;
        cin >> a >> b >> t;
        g[a].pb({b, t});
    }

    // Build segtree
    while (N % K) N++;
    sz = N / K;
    build();

    // Answer queries
    while (Q--) {
        int a, b;
        cin >> a >> b;

        Mat pmat = query(a / K, b / K - 1);
        int ans = pmat[b % K][a % K];
        cout << (ans == INF ? -1 : ans) << '\n';
    }

    return 0;
}