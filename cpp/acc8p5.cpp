// ./problem-5-u-turn-finesse.yml
#include <bits/stdc++.h>
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

const ll MOD = 998244353;

// Template is 1-indexed (by default).  Can be made 0-indexed by modifying Comp
// Example: update = point increment, range sum
// In the function applyUpdate, updates are applied from `v` to `to`
struct Comp {
    using Data = int;
    const Data vdef = 0;
    void applyUpdate(Data &to, Data &v) { to = (to+v)%MOD; }
    int transformInd(int idx, int N) { return idx+1; }
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

const int MN = 1e6 + 1;
int N,
    A[MN], dp[MN], dpr[MN];

void run(int dp[MN]) {
    BIT<Comp> bit; bit.init(N+1);
    dp[0] = 1;
    bit.update(0, 1);
    for (auto i = 1; i <= N; i++) {
        dp[i] = bit.query(A[i]-1);
        bit.update(A[i], dp[i]);
    }
}

void solve() {
    cin >> N;
    for (auto i = 1; i <= N; i++)
        cin >> A[i];

    run(dp);
    reverse(A+1, A+N+1);
    run(dpr);
    reverse(dpr+1, dpr+N+1);
    reverse(A+1, A+N+1);

    ll ans = 0;
    for (auto i = 1; i <= N; i++) {
        ans += ll(dp[i])*dpr[i]%MOD;
    }
    ans %= MOD;
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