// ./light-cyclin.yml
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

// Template is 1-indexed (by default).  Can be made 0-indexed by modifying Comp
// Default: Point increment and prefix sum query
struct Comp {
    using Data = int;
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

struct event {
    int t; ll x, a, b; // t=0->rem (a=y-value), t=1->query(a..b=y-values), t=2->add (a=y-value)
    bool operator<(const event &o) const {
        return x == o.x ? t < o.t : x < o.x;
    }
};
ostream& operator<<(ostream& out, const event o) {
    out << "(t=" << o.t << ", x=" << o.x << ", a=" << o.a << ", b=" << o.b << ")";
    return out;
}

const int MN = 1e5 + 1;
string tmp;

void solve() {
    vector<event> evt;
    cin >> (tmp);
    for (auto i = 0; i < 2; i++) {
        ll x, y; int n;
        cin >> x >> y >> n;
        for (auto j = 0; j < n; j++) {
            char d; ll v;
            cin >> d >> v;

            if (d == 'U') {
                evt.pb({1, x, y, y + v});
                y += v;
            }
            else if (d == 'D') {
                evt.pb({1, x, y - v, y});
                y -= v;
            }
            else if (d == 'R') {
                evt.pb({2, x, y, -1});
                evt.pb({0, x + v, y, -1});
                x += v;
            }
            else {
                evt.pb({2, x - v, y, -1});
                evt.pb({0, x, y, -1});
                x -= v;
            }
        }
    }

    sort(all(evt));
    BIT<Comp> bit; bit.init(1e6);
    ll ans = 0;
    for (auto &e : evt) {
        // cout<<"e="<<(e)<<", "; cout << endl; // db e
        if (e.t == 1) ans += bit.query(e.b) - bit.query(e.a - 1);
        else bit.update(e.a, e.t - 1);
    }
    cout << (ans) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        // Input
        
        solve();

        // Reset
    }
}