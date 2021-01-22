// ./tall.yml
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
// #include <ext/pb_ds/assoc_container.hpp> // Common file 
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds; 
// template <typename T, class comp = less<T>> using os_tree = tree<T, null_type, comp, rb_tree_tag, tree_order_statistics_node_update>;
// template <typename K, typename V, class comp = less<K>> using treemap = tree<K, V, comp, rb_tree_tag, tree_order_statistics_node_update>;
// HashSet
// #include <ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
const ll RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { ll operator()(ll x) const { return x ^ RANDOM; } };
// template <typename T, class Hash> using hashset = gp_hash_table<T, null_type, Hash>;
// template <typename K, typename V, class Hash> using hashmap = gp_hash_table<K, V, Hash>;
// More utilities
int SZ(string &v) { return v.length(); }
template <typename C> int SZ(C &v) { return v.size(); }
template <typename C> void UNIQUE(vector<C> &v) { sort(v.begin(), v.end()); v.resize(unique(v.begin(), v.end()) - v.begin()); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 2e5 + 1;
int N,
    val[MN];

bool cmp(const pii a, const pii b) {
    return a.fs == b.fs ? a.sn < b.sn : a.fs > b.fs;
}

pii solve(int bit, vector<int> vals) {
    if (vals.empty()) return mpr(0, 0);
    vector<int> lhs, rhs; //, lc, rc;
    for (auto &x : vals) {
        if ((x >> bit) & 1)
            rhs.pb(x ^ (1 << bit));
        else
            lhs.pb(x);
    }

    if (bit == 0) {
        if (lhs.size() && rhs.size()) return mpr(2, 0);
        else if (lhs.size()) return mpr(1, 0);
        else if (rhs.size()) return mpr(1, 1);
        return mpr(0, 0);
    }

    int want = 1 << (bit);
    if (SZ(lhs) == want) {
        pii rans = solve(bit-1, rhs);
        rans.fs += want;
        return rans;
    }
    if (SZ(rhs) == want) {
        pii ans = solve(bit-1, lhs);
        ans.fs += want;
        ans.sn |= (1 << bit);
        return ans;
    }

    auto rans = solve(bit-1, rhs);
    rans.sn |= (1 << bit);
    return min(solve(bit-1, lhs), rans, cmp);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> v(N);
        for (auto &x : v) cin >> x;
        UNIQUE(v);

        auto ans = solve(29, v);
        cout << (ans.fs) << ' ' << (ans.sn) << '\n';
    }

    return 0;
}