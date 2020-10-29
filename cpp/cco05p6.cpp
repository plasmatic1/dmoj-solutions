// ./cco-05-p6-windows.yml
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

struct pict {
    int a, b, c, d;
};

const pii BASE = mpr(-INF, -1);
const int MR = 10001, MN = 50001, LG = 14, MNODE = 1e7 + 1;
int R, C, N, Q;
pict ps[MN];

struct node {
    pii lz;
    int l, r;
    pii get() { return lz; }
} inner[MNODE];

int make() {
    static int ctr = 0;
    int res = ++ctr;
    assert(res < MNODE);
    inner[res] = {BASE, 0, 0};
    return res;
}

pii query(int x, int i, int l = 1, int r = C) {
    if (l > x || r < x || !i) return BASE;
    auto &n = inner[i];
    if (l == x && r == x) return n.get();
    int mid = (l + r) / 2;
    return max({n.get(), query(x, n.l, l, mid), query(x, n.r, mid + 1, r)});
}
void update(int ql, int qr, pii qv, int &i, int l = 1, int r = C) {
    if (ql > r || qr < l) return;
    if (!i) i = make();
    auto &n = inner[i];
    if (l >= ql && r <= qr) {
        maxa(n.lz, qv);
        return;
    }
    int mid = (l + r) / 2;
    update(ql, qr, qv, n.l, l, mid);
    update(ql, qr, qv, n.r, mid + 1, r);
}

#define MID int mid = (l + r) / 2, lhs = i + 1, rhs = i + (mid - l + 1) * 2;
int seg[MR * 2];

pii Query(int x, int y, int i = 1, int l = 1, int r = R) {
    if (l > x || r < x) return BASE;
    if (l == x && r == x) return query(y, seg[i]);
    MID;
    return max({query(y, seg[i]), Query(x, y, lhs, l, mid), Query(x, y, rhs, mid + 1, r)});
}
void Update(int qxl, int qxr, int qyl, int qyr, pii qv, int i = 1, int l = 1, int r = R) {
    if (qxl > r || qxr < l) return;
    if (l >= qxl && r <= qxr) {
        update(qyl, qyr, qv, seg[i]);
        return;
    }
    MID;
    Update(qxl, qxr, qyl, qyr, qv, lhs, l, mid);
    Update(qxl, qxr, qyl, qyr, qv, rhs, mid + 1, r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (R) >> (C) >> (N);

    for (auto i = 0; i < N; i++) { 
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        swap(b, d);
        ps[i] = {a, b, c, d};
        Update(a, c, b, d, mpr(i, i));
    }

    cin >> (Q);
    for (auto qn = N; qn < N+Q; qn++) {
        int a, b;
        cin >> a >> b;

        int q = Query(a, b).sn;
        cout << (q+1) << '\n';
        if (q != -1) {
            auto &p = ps[q];
            Update(p.a, p.c, p.b, p.d, mpr(qn, q));
        }
    }

    return 0;
}