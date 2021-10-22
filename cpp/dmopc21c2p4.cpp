// ./p4-water-mechanics.yml
#define DEBUG 0
#include <bits/stdc++.h>
using namespace std;

// Defines
#define fs first
#define sn second
#define pb push_back
#define eb emplace_back #define mpr make_pair
#define mtp make_tuple
#define all(x) (x).begin(), (x).end()
// Basic type definitions
#if __cplusplus == 201703L // CPP17 only things
template <typename T> using opt_ref = optional<reference_wrapper<T>>; // for some templates
#endif
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

// Example comparator: Range min + Range increment
// In the functions mergeLazy and applyLazy, objects are merged from `v` to `to`.  In the function merge, data is merged from left to right
struct Comp {
    using Data = int;
    using Lazy = int;
    const Data vdef = INF;
    const Lazy ldef = INF;
    Data merge(Data l, Data r) const { return min(l, r); }
    Lazy mergeLazy(Lazy to, Lazy v) const { return min(to, v); }
    void applyLazy(Data &to, Lazy &v, int l, int r) { mina(to, v); }
};
#define MID int mid = (l + r) / 2, lhs = i + 1, rhs = i + (mid - l + 1) * 2;
template <class Comp> struct LazySegmentTree {
    using Data = typename Comp::Data; using Lazy = typename Comp::Lazy; Comp C;
    int N;
    vector<Data> seg; vector<Lazy> lazy;
    void init(int n0) {
        N = n0;
        seg.assign(2 * N + 2, C.vdef);
        lazy.assign(2 * N + 2, C.ldef);
    }
    void push(int i, int l, int r) {
        if (lazy[i] != C.ldef) {
            MID;
            C.applyLazy(seg[i], lazy[i], l, r);
            if (l != r) {
                lazy[lhs] = C.mergeLazy(lazy[lhs], lazy[i]);
                lazy[rhs] = C.mergeLazy(lazy[rhs], lazy[i]);
            }
            lazy[i] = C.ldef;
        }
    }
    Data _query(int ql, int qr, int i, int l, int r) {
        if (ql > r || qr < l) return C.vdef;
        push(i, l, r);
        if (l >= ql && r <= qr) return seg[i];
        MID;
        return C.merge(_query(ql, qr, lhs, l, mid), _query(ql, qr, rhs, mid + 1, r));
    }
    Data _update(int ql, int qr, Lazy v, int i, int l, int r) {
        push(i, l, r);
        if (ql > r || qr < l) return seg[i];
        if (l >= ql && r <= qr) {
            lazy[i] = v;
            push(i, l, r);
            return seg[i];
        }
        MID;
        return seg[i] = C.merge(_update(ql, qr, v, lhs, l, mid), _update(ql, qr, v, rhs, mid + 1, r));
    }
    Data _setPoint(int q, Data v, int i, int l, int r) {
        push(i, l, r);
        if (q > r || q < l) return seg[i];
        if (l >= q && r <= q) return seg[i] = v;
        MID;
        return seg[i] = C.merge(_setPoint(q, v, lhs, l, mid), _setPoint(q, v, rhs, mid + 1, r));
    }
    Data query(int ql, int qr) { return _query(ql, qr, 1, 1, N); }
    void update(int ql, int qr, Lazy v) { _update(ql, qr, v, 1, 1, N); }
    void setPoint(int q, Data v) { _setPoint(q, v, 1, 1, N); }
};

// Template is 1-indexed
// Default Comp: RMQ + Set query
// Functions merge and applyUpdate should be implemented left to right
struct MaxComp {
    using Data = int;
    using Update = int;
    const Data vdef = -INF;
    Data merge(Data l, Data r) { return max(l, r); }
    void applyUpdate(Data &l, Update &r) { maxa(l, r); }
};
#define MID int mid = (l + r) / 2, lhs = i + 1, rhs = i + (mid - l + 1) * 2;
template <class Comp> struct SegmentTree {
    using Data = typename Comp::Data; using Update = typename Comp::Update; Comp C;
    int N;
    vector<Data> seg;
    void init(int n0) {
        N = n0;
        seg.assign(2 * N + 2, C.vdef);
    }
    Data _query(int ql, int qr, int i, int l, int r) {
        if (ql > r || qr < l) return C.vdef;
        if (l >= ql && r <= qr) return seg[i];
        MID;
        return C.merge(_query(ql, qr, lhs, l, mid), _query(ql, qr, rhs, mid + 1, r));
    }
    Data _update(int q, Update v, int i, int l, int r) {
        if (q > r || q < l) return seg[i];
        if (l == q && r == q) {
            C.applyUpdate(seg[i], v);
            return seg[i];
        }
        MID;
        return seg[i] = C.merge(_update(q, v, lhs, l, mid), _update(q, v, rhs, mid + 1, r));
    }
    Data query(int ql, int qr) { return _query(ql, qr, 1, 1, N); }
    void update(int q, Update v) { _update(q, v, 1, 1, N); }
};

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

const int MN = 1e6 + 1;
int N, K,
    H[MN], dp[MN];

Ranks<int> rs;
int L[MN], R[MN];

void calc(int L[MN]) {
    SegmentTree<MaxComp> seg; seg.init(SZ(rs));

    deque<int> dq{0};
    for (auto i = 1; i <= N; i++) {
        while (!dq.empty() && H[dq.back()] <= H[i])
            dq.pop_back();

        int idx = rs.get(H[i]), preUnder = seg.query(1, idx-1), preOver = dq.back()+1;
        if (preUnder < i-K)
            L[i] = max(i-K, preOver);
        else
            L[i] = max(L[preUnder], preOver);

        // update DS
        seg.update(idx, i);
        dq.pb(i);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;
    for (auto i = 1; i <= N; i++) {
        cin >> H[i];
        rs.add(H[i]);
    }
    H[0] = INF;
    rs.init();

    // do it twice!!!
    calc(L);
    reverse(H+1, H+N+1);
    calc(R);
    if (DEBUG) { cout<<"R=["; for(int __i=0; __i<((N+1)); __i++)cout<<(R)[__i]<<", "; cout<<"], ";cout << endl; } //__RAW_DEBUG_LINE__:db A:(N+1):R
    if (DEBUG) { cout<<"H=["; for(int __i=0; __i<((N+1)); __i++)cout<<(H)[__i]<<", "; cout<<"], ";cout << endl; } //__RAW_DEBUG_LINE__:db A:(N+1):H
    reverse(H+1, H+N+1);
    reverse(R+1, R+N+1);
    for (auto i = 1; i <= N; i++)
        R[i] = N-R[i]+1;

    memset(dp, 0x3f, sizeof dp);
    dp[0] = 0;

    LazySegmentTree<Comp> seg; seg.init(N);
    deque<pii> dq;
    for (auto i = 1; i <= N; i++) {
        // int l = i, r = i;

        // int ctr = K;
        // while (l > 1 && ctr > 0) {
        //     if (H[l-1] < H[l]) {
        //         ctr = K;
        //     }
        //     else if (H[l-1] > H[l]) {
        //         break;
        //     }
        //     else
        //         ctr--;
        //     l--;
        // }
        //
        // ctr = K;
        // while (r < N && ctr > 0) {
        //     if (H[r+1] < H[r]) {
        //         ctr = K;
        //     }
        //     else if (H[r+1] > H[r]) {
        //         break;
        //     }
        //     else
        //         ctr--;
        //     r++;
        // }

        // if (DEBUG) { cout<<"i="<<(i)<<", "; cout<<"l="<<(l)<<", "; cout<<"L[i]="<<(L[i])<<", "; cout<<"r="<<(r)<<", "; cout<<"R[i]="<<(R[i])<<", "; cout << endl; } //__RAW_DEBUG_LINE__:db i,l,L[i],r,R[i]
        // assert(L[i] == l);
        // assert(R[i] == r);

        // for (auto j = i; j <= r; j++) {
        //     mina(dp[j], dp[l-1]+1);
        // }

        seg.update(i, R[i], dp[L[i]-1]+1);
        dp[i] = seg.query(i, i);

        if (DEBUG) { cout<<"i="<<(i)<<", "; cout<<"L[i]="<<(L[i])<<", "; cout<<"R[i]="<<(R[i])<<", "; cout << endl; } //__RAW_DEBUG_LINE__:db i,L[i],R[i]
    }

    cout << (dp[N]) << '\n';

    return 0;
}