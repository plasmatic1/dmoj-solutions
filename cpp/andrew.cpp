// ./andrew-needs-help.yml
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

const ll MOD = 1e9 + 7;
ll fix(ll &&x) { x %= MOD; if (x < 0) x += MOD; return x; }
ll fix(ll &x) { x %= MOD; if (x < 0) x += MOD; return x; }
ll fpow(ll x, ll y, ll mod = MOD) {
    if (!y) return 1LL;
    return fpow(x * x % mod, y >> 1, mod) * ((y & 1) ? x : 1LL) % mod;
}
ll inv(ll x, ll mod = MOD) { return fpow(x, mod - 2, mod); }
// N choose R
vector<ll> fact, invf;
void init_nchooser(int MN) {
    fact.resize(MN + 1); invf.resize(MN + 1);
    fact[0] = invf[0] = 1LL;
    for (int i = 1; i <= MN; i++) {
        fact[i] = fix(fact[i - 1] * i);
        invf[i] = inv(fact[i]);
    }
}
ll choose(ll N, ll K) { return fix(fact[N] * fix(invf[K] * invf[N - K])); }
ll permute(ll N, ll K) { return fix(fact[N] * invf[N - K]); }
ll SB(ll stars, ll bars) { return choose(stars + bars - 1, bars - 1); }

/*
N choose K but the K objects must have non-adjacent indices

we have K+1 boxes: the ith box is the amount of non-chosen between K_(i-1) and K_i.  The contents of box 0 represent the offset of the first index.  Finally, the K+1th box represents any trailing 0s.  The rules are:

boxes 1 and K+1 can have any amount
boxes 2..K must have >=1

Additionally, the amount to distribute is N-K (since the K objects themselves are also part of the set).  Finally, note that in the original problem, N is actually N-1 since you can't place a bit at the last slot.

Therefore, the problem is just SB(N-K-K+1, K+1) where SB is stars/bars
*/

int N, D;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // init
    cin >> (N) >> (D);
    init_nchooser(N);

    // PIE
    ll ans = 0;
    for (auto i = N-D; i >= 1; i--) {
        // ll half = fix(SB(N - 1 - i - i + 1, i + 1) * fix(permute(N / 2, i) * fpow(2, i))), oth = fact[N - 2 * i], mul = i % 2 ? 1 : -1;
        ll half = fix(SB(N - 2 * i, i + 1) * fix(permute(N - D, i) * fpow(2, i))), oth = fact[N - 2 * i], mul = i % 2 ? 1 : -1;
        ans += fix(half * oth * mul); fix(ans);
    }

    cout << (ans) << '\n';

    return 0;
}