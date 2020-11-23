// ./coci-08-contest-4-6-periodni.yml
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

// PROBLEM HAS TREE STRUCTURE

// modulo
const ll MOD = 1e9 + 7;
ll fix(ll m) {
    m %= MOD;
    if (m < 0) m += MOD;
    return m;
}
ll fpow(ll x, ll y) {
    if (!y) return 1;
    return fix(fpow(fix(x * x), y >> 1) * ((y & 1) ? x : 1));
}
ll inv(ll x) { return fpow(x, MOD - 2); }

// n choose r
const int MV = 1e6 + 1;
ll fact[MV], invf[MV];
void init() {
    fact[0] = 1LL;
    for (auto i = 1; i < MV; i++) fact[i] = fix(fact[i - 1] * i);
    invf[MV-1] = inv(fact[MV-1]);
    for (auto i = MV-2; i >= 0; i--) invf[i] = fix(invf[i+1] * (i+1));
}
ll comb(int n, int k) {
    if (n < 0 || k < 0 || k > n) return 0LL;
    return fix(fact[n] * fix(invf[k] * invf[n-k]));
}
ll amul(int l, int r) { // l*(l+1)*...*r
    return fix(fact[r] * invf[l-1]);
}

const int MN = 501 + 10;
int N, K,
    H[MN];
ll dp[MN][MN];
int ctr = -1;

int solve(int l, int r, int preh) {
    if (l > r) return MN-1; // dp[0] is 1, dp[everything else]=0
    int c = ++ctr;
    auto cdp = dp[c];

    int minidx = min_element(H + l, H + r + 1) - H, c1 = solve(l, minidx-1, H[minidx]), c2 = solve(minidx+1, r, H[minidx]);

    // compute child dps
    auto dp0 = dp[c1], dp1 = dp[c2];
    ll tmp[MN]; memset(tmp, 0, sizeof tmp);
    for (auto i = 0; i <= K; i++)
        for (auto j = 0; j <= i; j++)
            tmp[i] = fix(tmp[i] + fix(dp0[j] * dp1[i-j]));

    // compute cdp array
    int w = r - l + 1, h = H[minidx] - preh;
    for (auto i = 0; i <= K; i++) {
        for (auto j = 0; j <= min(h, i); j++) {
            ll mul = fix(comb(w-(i-j), j) * amul(h-j+1, h));
            cdp[i] = fix(cdp[i] + mul * tmp[i-j]);
        }
    }

    return c;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (K);
    for (auto i = 0; i < N; i++)
        cin >> (H[i]);

    // init comb stuff
    init();
    dp[MN-1][0] = 1LL; // init default

    // get answer
    int c = solve(0, N-1, 0);
    cout << (dp[c][K]) << '\n';

    return 0;
}