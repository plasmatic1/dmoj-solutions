// figurines.yml
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

const int MN = 1e6 + 1, LIM = MN * 4;
int N, Q,
    A[MN], B[MN];

#define MID int mid = (l + r) / 2; \
                      int lhs = i * 2, rhs = i * 2 + 1;
struct LZ {
    int a, b;
} lazy[LIM];
struct Node {
    int max, maxA, maxB;
} seg[LIM];

void push(int i, int l, int r) {
    MID;
    auto &nd = seg[i];
    auto &lz = lazy[i];
    if (lz.a != INF) {
        nd.maxA = lz.a;
        nd.max = nd.maxB + lz.a;

        if (lhs < LIM) lazy[lhs].a = lz.a;
        if (rhs < LIM) lazy[rhs].a = lz.a;
        lz.a = INF;
    }
    if (lz.b != -INF) {
        nd.maxB = max(nd.maxB, lz.b);
        nd.max = max(nd.max, nd.maxA + lz.b);

        if (lhs < LIM) lazy[lhs].b = max(lazy[lhs].b, lz.b);
        if (rhs < LIM) lazy[rhs].b = max(lazy[rhs].b, lz.b);
        lz.b = -INF;
    }
}
void build(int i = 1, int l = 1, int r = N) {
    MID;
    lazy[i] = {INF, -INF};
    auto &nd = seg[i];
    nd.max = nd.maxB = nd.maxA = INT_MIN;
    for (auto j = l; j <= r; j++) {
        nd.max = max(nd.max, A[j] + B[j]);
        nd.maxB = max(nd.maxB, B[j]);
        nd.maxA = max(nd.maxA, A[j]);
    }
    if (l == r) return;
    build(lhs, l, mid); build(rhs, mid + 1, r);
}
void update(bool type, int ql, int qr, int qk, int i = 1, int l = 1, int r = N) {
    push(i, l, r);
    if (ql > r || qr < l) return;
    if (l >= ql && r <= qr) {
        if (type == 0) lazy[i].a = qk;
        else lazy[i].b = qk;
        push(i, l, r);
        return;
    }
    MID;
    update(type, ql, qr, qk, lhs, l, mid); update(type, ql, qr, qk, rhs, mid + 1, r);
    seg[i].maxB = max(seg[lhs].maxB, seg[rhs].maxB);
    seg[i].maxA = max(seg[lhs].maxA, seg[rhs].maxA);
    seg[i].max = max({seg[lhs].max, seg[rhs].max});
}
int query(int ql, int qr, int i = 1, int l = 1, int r = N) {
    if (ql > r || qr < l) return INT_MIN;
    push(i, l, r);
    if (l >= ql && r <= qr) return seg[i].max;
    MID;
    return max(query(ql, qr, lhs, l, mid), query(ql, qr, rhs, mid + 1, r));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (Q);
    for (auto i = 1; i <= N; i++)
        cin >> (A[i]);
    for (auto i = 1; i <= N; i++)
        cin >> (B[i]);

    build();

    while (Q--) {
        int T, l, r;
        cin >> T >> l >> r;
        if (T <= 2) {
            int k;
            cin >> k;
            update(T - 1, l, r, k);
        }
        else {
            int ans = query(l, r);
            cout << (ans) << '\n';
        }
    }

    return 0;
}