// coci-19-contest-6-5-trener.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define pb push_back
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
template <typename C> int SZ(C &v) { return v.size(); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const ll MOD = 1e9 + 7;
ll madd(ll a, ll b, ll mod = MOD) { return (a + b) % mod; }
ll msub(ll a, ll b, ll mod = MOD) { return (a - b + mod) % mod; }
ll mmul(ll a, ll b, ll mod = MOD) { return (a * b) % mod; }
ll fpow(ll x, ll y, ll mod = MOD) {
    if (!y) return 1LL;
    return mmul(fpow(mmul(x, x, mod), y >> 1, mod), (y & 1) ? x : 1LL, mod);
}
ll mdiv(ll x, ll y, ll mod = MOD) { return mmul(x, fpow(y, mod - 2, mod), mod); }

const int MN = 51, MK = 1501;
int N, K;
string ss[MN][MK];
ll dp[MN][MK];
map<string, vector<int>> has[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (K);
    for (auto i = 0; i < N; i++) {
        for (auto j = 0; j < K; j++) {
            cin >> (ss[i][j]);
            has[i][ss[i][j]].pb(j);
        }
    }

    // init dp
    for (auto i = 0; i < K; i++)
        dp[N - 1][i] = 1LL;

    // do dp
    for (auto i = N - 1; i > 0; i--) {
        for (auto j = 0; j < K; j++) {
            for (auto k = 0; k < 2; k++) {
                if (k == 1 && ss[i][j].substr(0, i) == ss[i][j].substr(1, i)) continue;
                for (auto to : has[i - 1][ss[i][j].substr(k, i)]) {
                    dp[i - 1][to] = madd(dp[i - 1][to], dp[i][j]); }
            }
        }
    }
    ll ans = 0;
    for (auto i = 0; i < K; i++)
        ans = madd(ans, dp[0][i]);
    cout << (ans) << '\n';

    return 0;
}