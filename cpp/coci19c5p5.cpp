// ./coci-19-contest-5-5-zapina.yml
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
const int MN = 351;
int N;
ll dp[MN][MN][2], fact[MN], invf[MN];

ll fpow(ll x, ll y) {
    if (!y) return 1;
    return (fpow((x * x) % MOD, y / 2) * ((y & 1) ? x : 1LL)) % MOD;
}
ll inv(ll x) { return fpow(x, MOD - 2); }
ll comb(int n, int k) { return (fact[n] * ((invf[k] * invf[n-k]) % MOD)) % MOD; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    dp[0][0][0] = 1LL;

    fact[0] = 1LL;
    for (auto i = 1; i < MN; i++) fact[i] = (fact[i-1]*i) % MOD;
    invf[MN-1] = inv(fact[MN-1]);
    for (auto i = MN-2; i >= 0; i--) invf[i] = (invf[i+1] * (i+1)) % MOD;

    for (auto i = 0; i < N; i++) {
        for (auto j = 0; j <= N; j++) {
            for (auto k = 0; k < 2; k++) {
                // no. to distribute
                for (auto l = 0; l <= N-j; l++) {
                    int newk = k || (l == i+1);
                    ll &alt = dp[i + 1][j + l][newk];
                    alt = (alt + (dp[i][j][k] * comb(N-j, l) % MOD)) % MOD;
                }
            }
        }
    }
    cout << (dp[N][N][1]) << '\n';

    return 0;
}