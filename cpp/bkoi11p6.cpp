// ./balkan-oi-11-p6-trapezoids.yml
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

const int MOD = 30013;

// Default: Point increment and prefix sum query
struct Comp {
    using Data = pii;
    const Data vdef = mpr(-1, 0);
    void applyUpdate(Data &to, Data &v) {
        if (v.fs > to.fs) to = v;
        else if (v.fs == to.fs) to.sn = (to.sn + v.sn) % MOD;
    }
    int transformInd(int idx, int N) { return idx; }
};
template <typename Comp> struct BIT {
    using Data = typename Comp::Data; Comp C;
    int N; vector<Data> bit;
    void init(int n0) {
        N = n0;
        bit.assign(N + 1, C.vdef);
    }
    void upd(int x, Data v) {
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

// top: a->b, bot: c->d
// ptQuery: (a, c), ptUpdate: (b, d)
struct Trap {
    int a, b, c, d;
};
istream& operator>>(istream &in, Trap &o) {
    in >> o.a >> o.b >> o.c >> o.d;
    return in;
}
struct Pt {
    int i, y;
};

const int MN = 1e5 + 1;
int N;
pii dp[MN];
Trap traps[MN];

vector<Pt> queries[MN * 2], updates[MN * 2];
Ranks<int> xs, ys;
BIT<Comp> bit;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);

    // input
    ys.add(-1);
    for (auto i = 0; i < N; i++) {
        cin >> (traps[i]);
        xs.add(traps[i].a); xs.add(traps[i].b);
        ys.add(traps[i].c); ys.add(traps[i].d);
    }
    xs.init(); ys.init();

    // init points on linesweep
    for (auto i = 0; i < N; i++) {
        auto &t = traps[i];
        queries[xs.get(t.a)].pb({i, ys.get(t.c)});
        updates[xs.get(t.b)].pb({i, ys.get(t.d)});
    }

    // linesweep
    bit.init(SZ(ys));
    bit.upd(ys.get(-1), mpr(0, 1));
    for (auto i = 1; i <= SZ(xs); i++) {
        for (auto &q : queries[i]) {
            dp[q.i] = bit.query(q.y - 1);
            dp[q.i].fs++;
        }
        for (auto &q : updates[i])
            bit.upd(q.y, dp[q.i]);
    }

    // get ans
    Comp c;
    pii ans = c.vdef;
    for (auto i = 0; i < N; i++) c.applyUpdate(ans, dp[i]);
    cout << (ans.fs) << ' ' << (ans.sn) << '\n';

    return 0;
}