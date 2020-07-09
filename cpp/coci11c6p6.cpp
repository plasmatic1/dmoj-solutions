// coci-11-contest-6-6-košare.yml
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
using ll = long long; using ull = unsigned long long; using ld = long double;
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

const ll MOD = 1e9 + 7;
ll madd(ll a, ll b, ll mod = MOD) { return (a + b) % mod; }
ll msub(ll a, ll b, ll mod = MOD) { return (a - b + mod) % mod; }
ll mmul(ll a, ll b, ll mod = MOD) { return (a * b) % mod; }
ll fpow(ll x, ll y, ll mod = MOD) {
    if (!y) return 1LL;
    return mmul(fpow(mmul(x, x, mod), y >> 1, mod), (y & 1) ? x : 1LL, mod);
}
ll mdiv(ll x, ll y, ll mod = MOD) { return mmul(x, fpow(y, mod - 2, mod), mod); }

// i am so bad :/
const int MN = 1e6 + 1, MM = 21, MSUB = 1 << (MM - 1);
int N, M;
ll p2[MN], cnt[MM][MSUB];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M);
    for (auto i = 1; i <= N; i++) {
        int k;
        cin >> k;
        int msk = 0;
        for (auto j = 0; j < k; j++) {
            int x;
            cin >> x;
            msk |= 1 << (x - 1);
        }
        cnt[0][msk]++;
    }

    int msub = 1 << M;
    for (auto i = 1; i <= M; i++) {
        for (auto j = 0; j < msub; j++) {
            cnt[i][j] = cnt[i - 1][j];
            if ((j >> (i - 1)) & 1)
                cnt[i][j] += cnt[i - 1][j ^ (1 << (i - 1))];
        }
    }

    p2[0] = 1LL;
    for (auto i = 1; i < MN; i++)
        p2[i] = mmul(p2[i - 1], 2);

    ll ans = 0;
    bool parity = M & 1;
    for (auto i = 0; i < msub; i++) {
        if ((__builtin_popcount(i) & 1) == parity)
            ans = madd(ans, p2[cnt[M][i]]);
        else
            ans = madd(ans, MOD - p2[cnt[M][i]]);
    }

    cout << (ans) << '\n';

    return 0;
}