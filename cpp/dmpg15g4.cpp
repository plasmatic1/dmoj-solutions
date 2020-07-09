// dmpg-15-g4-spacetime-convergence-cannons.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define pb push_back
#define fs first
#define sn second
#define mpr make_pair
#define mtp make_tuple
#define all(x) (x).begin(), (x).end()
// Basic type definitions
using ll = long long; using ull = unsigned long long;
using pii = pair<int, int>; using pll = pair<long, long>;
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
template <typename C> int sz(C &v) { return v.size(); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

struct Fr {
    ll n, d;
    void reduce() {
        ll gv = __gcd(abs(n), abs(d));
        n /= gv; d /= gv;
        if (d < 0) {
            n *= -1; d *= -1;
        }
    }
    Fr(ll a, ll b) : n(a), d(b) { 
        if (d == 0) {
            n = INF; d = 1; }
        else
            reduce(); 
    }
    Fr(ll x) : n(x), d(1) { reduce(); }
    Fr inv() const { return Fr(d, n); }
    Fr neg() const { return Fr(-n, d); }
    Fr mul(Fr f) const { return Fr(n * f.n, d * f.d); }
    Fr div(Fr f) const { return mul(f.inv()); }
    Fr add(Fr f) const { return Fr(n * f.d + f.n * d, d * f.d); }
    Fr sub(Fr f) const { return add(f.neg()); }
    bool operator==(const Fr o) const { return n == o.n && d == o.d; }
    bool operator!=(const Fr o) const { return n != o.n || d != o.d; }
    bool operator<(const Fr o) const { return n * o.d < o.n * d; }
    bool operator>(const Fr o) const { return o < *this; }
};
ostream& operator<<(ostream &out, const Fr o) {
    out << o.n << " / " << o.d;
    return out;
}

using pif = pair<int, Fr>;

ostream& operator<<(ostream& out, const pif o) {
    out << "(first=" << o.first << ", second=" << o.second << ")";
    return out;
}

bool pifCmp(const pif &a, const pif &b) {
    return a.second == b.second ? a.first < b.first : a.second < b.second;
}

bool itemCmp(const pair<pif, int> &a, const pair<pif, int> &b) {
    return pifCmp(a.first, b.first);
}

const int MN = 2e5 + 1;
int N, X,
    xs[MN], ys[MN];

ll bit[MN];
void add(int x, ll v) {
    for (; x < MN; x += x & -x)
        bit[x] += v;
}
ll sum(int x) {
    ll sum = 0;
    for (; x; x -= x & -x)
        sum += bit[x];
    return sum;
}

vector<pif> ranks;
vector<pair<pif, int>> its;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (X);
    for (auto i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        xs[i] = x; ys[i] = y;
        ranks.emplace_back(y, Fr(y, x));
        its.emplace_back(mpr(y, Fr(y, X - x)), i);
    }
    
    // processing
    sort(all(its), itemCmp);
    reverse(all(its));
    sort(all(ranks), pifCmp);
    
    ll ans = 0;
    for (auto pp : its) {
        Fr xval(ys[pp.second], xs[pp.second]);
        int xid = lower_bound(all(ranks), mpr(ys[pp.second], xval), pifCmp) - ranks.begin() + 1;
        ll qv = sum(xid); ans += qv * qv;
        add(1, 1); add(xid + 1, -1);
    }

    cout << (ans) << '\n';

    return 0;
}