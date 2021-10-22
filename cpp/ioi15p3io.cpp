// ./ioi-15-p3-teams-standard-io.yml
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

// template is 1-indexed
template <typename T> struct Ranks {
    vector<T> ranks;
    void init() {
        sort(ranks.begin(), ranks.end());
        ranks.resize(unique(ranks.begin(), ranks.end()) - ranks.begin());
    }
    template <typename It> void init(It st, It en) { ranks = vector<T>(st, en); init(); }
    void add(T v) { ranks.push_back(v); }
    int get(T v) { return lower_bound(ranks.begin(), ranks.end(), v) - ranks.begin() + 1; }
    int size() { return ranks.size(); }
};

Ranks<pii> rb, ra;

const int MN = 5e5 + 1, LIM = 2e7;

struct node {
    int l, r;
    int sum;
} NS[LIM];
int _ptr = 0;

int mk(int v) {
    NS[++_ptr] = {0, 0, v};
    return _ptr;
}
int mk(int l, int r) {
    NS[++_ptr] = {l, r, NS[l].sum + NS[r].sum};
    return _ptr;
}

int build(int l, int r) {
    if (l == r) return mk(0);
    int mid = (l+r) / 2;
    return mk(build(l, mid), build(mid+1, r));
}
int upd(int rt, int l, int r, int q) {
    if (l == q && r == q) return mk(NS[rt].sum + 1);
    int mid = (l+r) / 2;
    if (q <= mid) return mk(upd(NS[rt].l, l, mid, q), NS[rt].r);
    return mk(NS[rt].l, upd(NS[rt].r, mid+1, r, q));
}

using T = tuple<int, int, int>; // ordering in pseg: 

int N,
    A[MN], B[MN];
int rt[MN];

void init(int N0, int A0[], int B0[]) {
    N = N0;
    copy(A0, A0+N, A);
    copy(B0, B0+N, B);

    // init pseg and rank compress
    vector<pii> ts;
    for (auto i = 0; i < N; i++) {
        rb.add({B[i], i});
        ra.add({A[i], i});
        ts.eb(A[i], i);
    }
    ra.init(); rb.init();
    sort(all(ts));

    rt[0] = build(1, SZ(rb));
    int ctr = 0;
    for (auto [_, i] : ts) {
        ctr++;
        rt[ctr] = upd(rt[ctr-1], 1, SZ(rb), rb.get({B[i], i}));
    }
    // we dun here
}

int query(int rtl, int rtr, int ql, int qr, int l=1, int r=SZ(rb)) {
    if (ql > r || qr < l) return 0;
    if (ql <= l && r <= qr) return NS[rtr].sum - NS[rtl].sum;
    int mid = (l+r) / 2;
    return query(NS[rtl].l, NS[rtr].l, ql, qr, l, mid) + query(NS[rtl].r, NS[rtr].r, ql, qr, mid+1, r);
}

int walk(int rtl, int rtr, int want, int l=1, int r=SZ(rb)) {
    int cs = (l == r ? NS[rtr].sum - NS[rtl].sum : NS[NS[rtr].l].sum - NS[NS[rtl].l].sum);
    if (l == r) return cs == want ? l : -1;
    int mid = (l+r) / 2;
    if (want > cs) return walk(NS[rtl].r, NS[rtr].r, want - cs, mid+1, r);
    else return walk(NS[rtl].l, NS[rtr].l, want, l, mid);
}

int can(int M, int K[]) {
    sort(K, K+M);

    // use pseg to do a linesweep but zoom zoom
    vector<pii> dq{{SZ(rb)+1, 0}};
    for (auto i = 0; i < M; i++) {
        int idx = upper_bound(all(ra.ranks), pii(K[i], INF)) - ra.ranks.begin(), b = rb.get(pii(K[i], -INF))-1;

        while (dq.back().fs <= b) dq.pop_back();

        int want = K[i];
        while (want > 0) {
            if (dq.empty()) return 0;
            auto [pb, pa] = dq.back();

            int full = query(rt[pa], rt[idx], b+1, pb);
            if (full <= want) {
                b = pb;
                want -= full;
                dq.pop_back();
            }
            else {
                int pre = query(rt[pa], rt[idx], 1, b), ans = walk(rt[pa], rt[idx], want+pre);
                want = 0;
                b = ans;
            }
        }
        dq.eb(b, idx);
    }

    return 1;
}

#define LOCAL
#ifdef LOCAL
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    int a[n], b[n];
    for (auto i = 0; i < n; i++) cin >> a[i] >> b[i];
    init(n, a, b);
    int q; cin >> q;
    for (auto i = 0; i < q; i++) {
        int m; cin >> m;
        int k[m];
        for (auto j = 0; j < m; j++) cin >> k[j];
        cout << (can(m, k)) << '\n';
    }

    return 0;
}
#endif