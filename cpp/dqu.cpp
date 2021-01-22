// ./division-queries-and-updates.yml
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
#ifdef __GNUG__
// PBDS order statistic tree
#include <ext/pb_ds/assoc_container.hpp> // Common file 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; 
template <typename T, class comp = less<T>> using os_tree = tree<T, null_type, comp, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename V, class comp = less<K>> using treemap = tree<K, V, comp, rb_tree_tag, tree_order_statistics_node_update>;
// HashSet
#include <ext/pb_ds/assoc_container.hpp>
template <typename T, class Hash> using hashset = gp_hash_table<T, null_type, Hash>;
template <typename K, typename V, class Hash> using hashmap = gp_hash_table<K, V, Hash>;
const ll RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { ll operator()(ll x) const { return x ^ RANDOM; } };
#endif
// More utilities
int SZ(string &v) { return v.length(); }
template <typename C> int SZ(C &v) { return v.size(); }
template <typename C> void UNIQUE(vector<C> &v) { sort(v.begin(), v.end()); v.resize(unique(v.begin(), v.end()) - v.begin()); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

ostream& operator<<(ostream& out, const pii o) {
    out << "(fs=" << o.fs << ", sn=" << o.sn << ")";
    return out;
}

#ifdef LOCAL
const int B = 2;
#else
const int B = 700;
#endif

struct evt {
    int i, id, until;
    bool operator<(const evt &o) const {
        return until > o.until;
    }
};
ostream& operator<<(ostream& out, const evt o) {
    out << "(i=" << o.i << ", id=" << o.id << ", until=" << o.until << ")";
    return out;
}

const int MN = 2e5 + 1, BCNT = MN/B+10;
int N, Q,
    bit[MN];

void add(int x) { for (; x <= N; x += x & -x) bit[x]++; }
int query(int x) { mina(x, N); int res = 0; for (; x; x -= x & -x) res += bit[x]; return res; }

pii seg[MN*2];
int lazy[MN*2];
#define MID int mid = (l + r) / 2, lhs = i + 1, rhs = i + (mid - l + 1) * 2;
void push(int i, int l, int r) {
    if (lazy[i]) {
        seg[i].fs += lazy[i];
        if (l != r) {
            MID;
            lazy[lhs] += lazy[i];
            lazy[rhs] += lazy[i];
        }
        lazy[i] = 0;
    }
}
pii upd(int ql, int qr, int qv, int i = 1, int l = 1, int r = N) {
    push(i, l, r);
    if (ql > r || qr < l) return seg[i];
    if (l >= ql && r <= qr) {
        lazy[i] = qv;
        push(i, l, r);
        return seg[i];
    }
    MID;
    return seg[i] = min(upd(ql, qr, qv, lhs, l, mid), upd(ql, qr, qv, rhs, mid+1, r));
}
pii query(int ql, int qr, int i = 1, int l = 1, int r = N) {
    if (ql > r || qr < l) return mpr(INF, -1);
    push(i, l, r);
    if (l >= ql && r <= qr) return seg[i];
    MID;
    return min(query(ql, qr, lhs, l, mid), query(ql, qr, rhs, mid+1, r));
}
pii build(int i = 1, int l = 1, int r = N) {
    if (l == r) return seg[i] = mpr(l, l);
    MID;
    return seg[i] = min(build(lhs, l, mid), build(rhs, mid + 1, r));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (Q);
    mina(N, Q);
    build();

    while (Q--) {
        int T, l, r;
        cin >> T >> l >> r;
        if (T == 1) {
            if (r > N) r = N;
            if (l > N) continue;

            upd(l, r, -1);
            auto q = query(1, N);
            while (q.fs <= 0) {
                add(q.sn);
                upd(q.sn, q.sn, q.sn);
                q = query(1, N);
            }
        }
        else
            cout << (query(r) - query(l-1)) << '\n';
    }

    return 0;
}