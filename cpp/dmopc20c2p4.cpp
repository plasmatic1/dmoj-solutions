// ./dmopc-20-contest-2-p4-hungry-pigeons.yml
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

// // Thanks wesley thanks wesley thanks wesley
// // RMQ + Increment query
// struct Comp {
//     using Data = int;
//     using Lazy = int;
//     const Data vdef = 0;
//     const Lazy ldef = 0;
//     Data merge(Data l, Data r) const { return min(l, r); }
//     Lazy mergeLazy(Lazy l, Lazy r) const { return l + r; }
//     void applyLazy(Data &to, Lazy &v, int l, int r) { to += v; }
// };
// #define MID int mid = (l + r) / 2, lhs = i + 1, rhs = i + (mid - l + 1) * 2;
// template <class Comp> struct LazySegmentTree {
//     using Data = typename Comp::Data; using Lazy = typename Comp::Lazy; Comp C;
//     int N;
//     vector<Data> seg; vector<Lazy> lazy;
//     void init(int n0) {
//         N = n0;
//         seg.assign(2 * N + 2, C.vdef);
//         lazy.assign(2 * N + 2, C.ldef);
//     }
//     void push(int i, int l, int r) {
//         if (lazy[i] != C.ldef) {
//             MID;
//             C.applyLazy(seg[i], lazy[i], l, r);
//             if (l != r) {
//                 lazy[lhs] = C.mergeLazy(lazy[lhs], lazy[i]);
//                 lazy[rhs] = C.mergeLazy(lazy[rhs], lazy[i]);
//             }
//             lazy[i] = C.ldef;
//         }
//     }
//     Data _query(int ql, int qr, int i, int l, int r) {
//         if (ql > r || qr < l) return C.vdef;
//         push(i, l, r);
//         if (l >= ql && r <= qr) return seg[i];
//         MID;
//         return C.merge(_query(ql, qr, lhs, l, mid), _query(ql, qr, rhs, mid + 1, r));
//     }
//     Data _update(int ql, int qr, Lazy v, int i, int l, int r) {
//         push(i, l, r);
//         if (ql > r || qr < l) return seg[i];
//         if (l >= ql && r <= qr) {
//             lazy[i] = v;
//             push(i, l, r);
//             return seg[i];
//         }
//         MID;
//         return seg[i] = C.merge(_update(ql, qr, v, lhs, l, mid), _update(ql, qr, v, rhs, mid + 1, r));
//     }
//     Data query(int ql, int qr) { return _query(ql, qr, 1, 1, N); }
//     void update(int ql, int qr, Lazy v) { _update(ql, qr, v, 1, 1, N); }
// };


struct C {
        using Data = int;
        using Lazy = int;
        static Data qdef() { return 0; }
        static Lazy ldef() { return 0; }
        static Data merge(const Data &l, const Data &r) { return min(l, r); }
        static Data applyLazy(const Data &l, const Lazy &r) { return l + r; }
        static Lazy getSegmentVal(const Lazy &v, int k) { return v; }
        static Lazy mergeLazy(const Lazy &l, const Lazy &r) { return l + r; }
      };
template <class C> struct SegmentTreeLazyBottomUp {
  using Data = typename C::Data; using Lazy = typename C::Lazy;
  int N, lgN; vector<Data> TR; vector<Lazy> LZ;
  void apply(int i, const Lazy &v, int k) {
    TR[i] = C::applyLazy(TR[i], C::getSegmentVal(v, k));
    if (i < N) LZ[i] = C::mergeLazy(LZ[i], v);
  }
  void eval(int i, int k) {
    TR[i] = C::merge(TR[i * 2], TR[i * 2 + 1]); if (LZ[i] != C::ldef())
      TR[i] = C::applyLazy(TR[i], C::getSegmentVal(LZ[i], k));
  }
  void propagate(int i) {
    int h = lgN + 1, k = 1 << lgN, ii = i >> h;
    for (; h > 0; ii = i >> --h, k /= 2) if (LZ[ii] != C::ldef()) {
      apply(ii * 2, LZ[ii], k); apply(ii * 2 + 1, LZ[ii], k);
      LZ[ii] = C::ldef();
    }
  }
  template <class F> SegmentTreeLazyBottomUp(int N, F f)
      : N(N), lgN(N == 0 ? 0 : __lg(N)),
        TR(N * 2, C::qdef()), LZ(N, C::ldef()) {
    generate(TR.begin() + N, TR.end(), f);
    for (int i = N - 1; i > 0; i--) TR[i] = C::merge(TR[i * 2], TR[i * 2 + 1]);
  }
  template <class It> SegmentTreeLazyBottomUp(It st, It en)
      : SegmentTreeLazyBottomUp(en - st, [&] { return *st++; }) {}
  SegmentTreeLazyBottomUp(int N, const Data &vdef)
      : SegmentTreeLazyBottomUp(N, [&] { return vdef; }) {}
  void update(int l, int r, const Lazy &v) {
    propagate(l += N); propagate(r += N); bool bl = 0, br = 0; int k = 1;
    for (; l <= r; l /= 2, r /= 2, k *= 2) {
      if (bl) eval(l - 1, k);
      if (br) eval(r + 1, k);
      if (l % 2) { apply(l++, v, k); bl = 1; }
      if (!(r % 2)) { apply(r--, v, k); br = 1; }
    }
    for (l--, r++; r; l /= 2, r /= 2, k *= 2) {
      if (bl) eval(l, k);
      if (br && (!bl || l != r)) eval(r, k);
    }
  }
  Data query(int l, int r) {
    propagate(l += N); propagate(r += N); Data ql = C::qdef(), qr = C::qdef();
    for (; l <= r; l /= 2, r /= 2) {
      if (l % 2) ql = C::merge(ql, TR[l++]);
      if (!(r % 2)) qr = C::merge(TR[r--], qr);
    }
    return C::merge(ql, qr);
  }
};

// template is 1-indexed
template <typename T> struct Ranks {
    vector<T> ranks;
    void init() {
        sort(ranks.begin(), ranks.end());
        ranks.resize(unique(ranks.begin(), ranks.end()) - ranks.begin());
    }
    template <typename It> void init(It st, It en) { ranks = vector<T>(st, en); init(); }
    void add(T v) { ranks.pb(v); }
    int get(T v) { return lower_bound(ranks.begin(), ranks.end(), v) - ranks.begin() + 1; }
    int size() { return ranks.size(); }
};

// observation: ans can increase at most M/N times
// Complexity: O(NlogM * M/N + MlogM) = O(MlogM)
const int MN = 5e4 + 1, MM = 5e5 + 1;
int N, M,
    B[MN], D[MM];
SegmentTreeLazyBottomUp<C> seg(1, 0);
Ranks<int> r;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M);
    for (auto i = 0; i < N; i++) {
        cin >> (B[i]);
        B[i]--;
        r.add(B[i]);
    }
    for (auto i = 0; i < M; i++) {
        cin >> (D[i]);
        // r.add(D[i]);
    }
    
    // init DS
    r.init();
    seg = SegmentTreeLazyBottomUp<C>(SZ(r)+10, 0);

    int ans = -1;
    for (auto i = 0; i < M; i++) {
        seg.update(r.get(D[i]), SZ(r), 1);
        while (seg.query(1, SZ(r)) >= 0) {
            ans++;
            for (auto j = 0; j < N; j++)
                seg.update(r.get(B[j]), SZ(r), -1);
        }
        cout << ans << ' ';
    }
    cout << '\n';

    return 0;
}