// ./dominoes.yml
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

// Template is 1-indexed (by default).  Can be made 0-indexed by modifying Comp
// Default: Point increment and prefix sum query
struct CompL {
    using Data = int;
    const Data vdef = INF;
    void applyUpdate(Data &to, Data v) { mina(to, v); }
    int transformInd(int idx, int N) { return N - idx + 1; }
};
struct CompR {
    using Data = int;
    const Data vdef = -INF;
    void applyUpdate(Data &to, Data v) { maxa(to, v); }
    int transformInd(int idx, int N) { return idx; }
};
template <typename Comp> struct BIT {
    using Data = typename Comp::Data; Comp C;
    int N; vector<Data> bit;
    void init(int n0) {
        N = n0;
        bit.assign(N + 1, C.vdef);
    }
    void update(int x, Data v) {
        x = C.transformInd(x, N);
        for (; x <= N; x += x & -x)
            C.applyUpdate(bit[x], v);
    }
    Data query(int x) {
        x = C.transformInd(x, N);
        Data res = C.vdef;
        for (; x; x -= x & -x)
            C.applyUpdate(res, bit[x]);
        return res;
    }
};

const int MN = 1e5 + 1;
int N,
    lhs[MN], rhs[MN], dp[MN];
pii dom[MN];
Ranks<int> rs;
vector<int> g[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    for (auto i = 1; i <= N; i++) {
        cin >> (dom[i].fs) >> (dom[i].sn);
        int l = dom[i].fs, h = dom[i].sn;
        rs.add(l); rs.add(l+h); rs.add(l-h);
    }
    sort(dom + 1, dom + N + 1);
    rs.init();

    // build LHS and RHS
    // LHS[i] -> furthest domino reachable by knocking domino i left
    // RHS[i] -> furthest domino reachable by knocking domino i right
    BIT<CompL> bitl; bitl.init(SZ(rs));
    for (auto i = 1; i <= N; i++) {
        int q = bitl.query(rs.get(dom[i].fs - dom[i].sn));
        lhs[i] = min(i, q);
        bitl.update(rs.get(dom[i].fs), lhs[i]);
    }

    BIT<CompR> bitr; bitr.init(SZ(rs));
    for (auto i = N; i >= 1; i--) {
        int q = bitr.query(rs.get(dom[i].fs + dom[i].sn));
        rhs[i] = max(i, q);
        bitr.update(rs.get(dom[i].fs), rhs[i]);
    }

    // dp!!!
    memset(dp, 0x3f, sizeof dp); dp[0] = 0;
    bitl.init(N);
    for (auto i = 0; i <= N; i++) {
        mina(dp[i], bitl.query(lhs[i]));
        if (i < N) {
            mina(dp[rhs[i + 1]], dp[i] + 1);
            bitl.update(i + 1, dp[i] + 1);
        }
    }

    cout << (dp[N]) << '\n';

    return 0;
}