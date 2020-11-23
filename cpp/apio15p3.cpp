// ./apio-15-p3-palembang-bridges.yml
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
struct Comp {
    using Data = ll;
    const Data vdef = 0;
    void applyUpdate(Data &to, Data &v) { to += v; }
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

struct seg {
    int l, r;
    bool operator<(const seg &o) const {
        return l + r < o.l + o.r;
    }
};
ostream& operator<<(ostream& out, const seg o) {
    out << "(l=" << o.l << ", r=" << o.r << ")";
    return out;
}

const int MN = 1e5 + 1;
int K, N;
ll initial = 0;
vector<seg> ss;
Ranks<int> rs;

BIT<Comp> suml, cntl, sumr, cntr;

// assuming ds has already been built
ll check(int pos) {
    ll lhs = rs.ranks[pos] * cntl.query(pos + 1) - suml.query(pos + 1),
       rhs = (sumr.query(SZ(rs)) - sumr.query(pos + 1)) - rs.ranks[pos] * (cntr.query(SZ(rs)) - cntr.query(pos + 1));
    return lhs + rhs;
}
// assumes ds has already been built for ll...rr
ll best() {
    if (SZ(rs) < 2) return check(0);
    int l = 0, r = SZ(rs) - 1;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (check(mid) >= check(mid + 1))
            l = mid;
        else
            r = mid;
    }
    return min(check(l), check(l + 1));
}

void change(seg &s, ll mul) {
    int rankL = rs.get(s.l), rankR = rs.get(s.r);
    suml.update(rankR, s.r * mul);
    cntl.update(rankR, mul);
    sumr.update(rankL, s.l * mul);
    cntr.update(rankL, mul);
}
void resetBIT() {
    suml.init(SZ(rs)); cntl.init(SZ(rs));
    sumr.init(SZ(rs)); cntr.init(SZ(rs));
}

// K=2 things
ll sto[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (K) >> (N);
    for (auto i = 0; i < N; i++) {
        char t1; int p1; char t2; int p2;
        cin >> t1 >> p1 >> t2 >> p2;
        initial += abs(p1 - p2);
        if (t1 != t2) {
            initial++;
            if (p1 > p2) swap(p1, p2);
            ss.pb({p1, p2});
        }
        rs.add(p1); rs.add(p2);
    }
    rs.init();
    resetBIT();
    // cout << "ss=["; for (auto x:ss)cout<<x<<", "; cout<<"], "; cout << endl; // db I:ss

    ll ans = !ss.empty() * LLINF;
    if (K == 1) {
        for (auto &s : ss)
            change(s, 1);
        ans = best();
    }
    else {
        sort(all(ss));
        for (auto i = 0; i < SZ(ss); i++) {
            change(ss[i], 1);
            sto[i] = best();
        }
        resetBIT();
        for (auto i = SZ(ss)-1; i >= 0; i--) {
            change(ss[i], 1);
            ll cans = best();
            if (i > 0) cans += sto[i - 1];
            mina(ans, cans);
        }
    }
    
    // cout<<"initial="<<(initial)<<", "; cout << endl; // db initial
    cout << (ans*2+initial) << '\n';

    return 0;
}