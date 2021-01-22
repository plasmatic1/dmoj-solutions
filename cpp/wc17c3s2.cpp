// ./wc-17-contest-3-s2-gleamingproudchickenfunrun.yml
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

struct Seg {
    int l, r;
    bool operator<(const Seg &o) const {
        return r == o.r ? l > o.l : r < o.r;
    }
};
istream& operator>>(istream &in, Seg &o) {
    return in >> o.l >> o.r;
}

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
struct Comp {
    using Data = int;
    const Data vdef = INF;
    void applyUpdate(Data &to, Data &v) { mina(to, v); }
    int transformInd(int idx, int N) { return N - idx + 1; }
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

const int MN = 3e5 + 1;
int N,
    dp[MN];
Seg ss[MN];
pii LR[MN];
Ranks<int> rs;
BIT<Comp> bit;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int minR = INF;
    cin >> (N);
    for (auto i = 1; i <= N; i++) {
        cin >> ss[i];
        LR[i] = {ss[i].l, ss[i].r};
        mina(minR, ss[i].r);
        rs.add(ss[i].l);
        rs.add(ss[i].r);
    }
    rs.init();
    bit.init(SZ(rs));
    sort(ss + 1, ss + N + 1);
    // Indexed by L, suffix max of R
    sort(LR + 1, LR + N + 1);
    for (auto i = N-1; i >= 1; i--)
        mina(LR[i].sn, LR[i+1].sn);

    memset(dp, INF, sizeof dp);
    int ans = INF;
    for (auto i = 1; i <= N; i++) {
        // can start
        if (ss[i].l < minR) dp[i] = 1;
        mina(dp[i], bit.query(rs.get(ss[i].l)+1) + 1);
        // for (auto j = 1; j < i; j++)
        //     if (ss[i].l < R[j])
        //         mina(dp[i], dp[j]+1);

        int idx = lower_bound(LR + 1, LR + N + 1, mpr(ss[i].r, -1)) - LR;
        if (idx > N) ans = min(ans, dp[i]);
        else {
            int rv = LR[idx].sn;
            bit.update(rs.get(rv), dp[i]);
        }
    }

    cout << (ans) << '\n';

    return 0;
}