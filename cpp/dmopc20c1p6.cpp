// ./dmopc-20-contest-1-p6-victor-identifies-software.yml
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


const int MN = 3e5 + 10;
const ll bad = -3e11; // thank god for |a_i|<=1e5
int N, Q,
    val[MN];

struct node {
    ll mx, p, s, sum;
};
struct lazyp {
    int lset, lsetval;
};

int cnt1[MN * 2];
node seg[MN * 2][2];
node segclr[MN * 2][2];
node segf[MN * 2];
lazyp lazy[MN * 2];

// combiners
void reset(node n[2]) {
    for (auto i = 0; i < 2; i++)
        n[i] = {bad, bad, bad, bad};
}

node combine(node l, node r) {
    node res;
    res.p = max(l.p, l.sum + r.p);
    res.s = max(r.s, r.sum + l.s);
    res.mx = max({l.mx, r.mx, l.s + r.p});
    res.sum = l.sum + r.sum;
    return res;
}

#define MID int mid = (l + r) / 2, lhs = i + 1, rhs = i + (mid - l + 1) * 2;
#define N(i) auto &n = seg[i], &nc = segclr[i]; auto &nf = segf[i];
#define SEG_COMBINE nf = combine(segf[lhs], segf[rhs]); \
    for (auto j = 0; j < 2; j++) { \
        n[j] = combine(seg[lhs][j], seg[rhs][j]); \
        nc[j] = combine(segclr[lhs][j], segclr[rhs][j]); \
    } \
    cnt1[i] = cnt1[lhs] + cnt1[rhs];

// build
void build(int i = 1, int l = 1, int r = N) {
    lazy[i] = {-1, INF};
    N(i);
    if (l == r) {
        node vn{val[l], val[l], val[l], val[l]}, bn{bad, bad, bad, bad};
        n[0] = nf = vn;
        nc[0] = {1, 1, 1, 1};
        n[1] = nc[1] = bn;
        return;
    }
    MID;
    build(lhs, l, mid); build(rhs, mid + 1, r);
    SEG_COMBINE;
}

// push
void push(int i, int l, int r) {
    auto &lz = lazy[i];
    N(i);
    ll sz = r - l + 1;
    if (lz.lset != -1) {
        reset(n); reset(nc);
        n[lz.lset] = nf;
        nc[lz.lset] = {sz, sz, sz, sz};
        cnt1[i] = sz * lz.lset;

        if (l != r) {
            MID;
            lazy[lhs].lset = lz.lset;
            lazy[rhs].lset = lz.lset;
        }
        lz.lset = -1;
    }

    if (lz.lsetval != INF) {
        ll v = lz.lsetval, vsum = v * sz;

        if (v > 0) nf = {vsum, vsum, vsum, vsum};
        else nf = {v, v, v, vsum};
        
        // nc[j] (except for sum), should only include X number of 1s or 1 bad.  One call to maxa should suffice to fix it
        ll cnt[2] = {sz - cnt1[i], cnt1[i]};
        for (auto j = 0; j < 2; j++) {
#define ASSIGN(prop) n[j].prop = nc[j].prop > 0 ? (v > 0 ? nc[j].prop * v : v) : bad;
            ASSIGN(mx); ASSIGN(p); ASSIGN(s);
            n[j].sum = cnt[j] * v + cnt[!j] * bad;
        }

        if (l != r) {
            MID;
            lazy[lhs].lsetval = lz.lsetval;
            lazy[rhs].lsetval = lz.lsetval;
        }
        lz.lsetval = INF;
    }
}

// update
void update(int ql, int qr, int qtype, int qv, int i = 1, int l = 1, int r = N) {
    push(i, l, r);
    if (l > qr || r < ql) return;
    if (l >= ql && r <= qr) {
        if (qtype == 0) lazy[i].lset = qv;
        else lazy[i].lsetval = qv;
        push(i, l, r);
        return;
    }
    MID;
    update(ql, qr, qtype, qv, lhs, l, mid); update(ql, qr, qtype, qv, rhs, mid + 1, r);
    N(i); SEG_COMBINE;
}

node query(int ql, int qr, int qt, int i = 1, int l = 1, int r = N) {
    if (l > qr || r < ql) return {bad, bad, bad, bad};
    push(i, l, r);
    if (l >= ql && r <= qr) return seg[i][qt];
    MID;
    return combine(query(ql, qr, qt, lhs, l, mid), query(ql, qr, qt, rhs, mid + 1, r));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (Q);
    for (auto i = 1; i <= N; i++)
        cin >> (val[i]);

    build();
    while (Q--) {
        int T, l, r;
        cin >> T >> l >> r;
        if (1 <= T && T <= 2) {
            T -= 1;
            update(l, r, 0, T);
        }
        else if (T == 3) {
            int v;
            cin >> v;
            update(l, r, 1, v);
        }
        else {
            T -= 4;
            auto qans = query(l, r, T);
            if (qans.mx <= bad)
                cout << ("breaks galore") << '\n';
            else 
                cout << (qans.mx) << '\n';
        }
    }

    return 0;
}