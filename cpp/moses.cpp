// ./moses-needs-help.yml
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

const ll MOD = 1e9 + 7;
ll fix(ll &&x) { x %= MOD; if (x < 0) x += MOD; return x; }
ll fix(ll &x) { x %= MOD; if (x < 0) x += MOD; return x; }
ll fpow(ll x, ll y, ll mod = MOD) {
    if (!y) return 1LL;
    return fpow(x * x % mod, y >> 1, mod) * ((y & 1) ? x : 1LL) % mod;
}
ll inv(ll x, ll mod = MOD) { return fpow(x, mod - 2, mod); }

const int MN = 1e6+1;
int N, P;
ll A[MN], fact[MN], invf[MN], psum[MN];

// NcK mod P
ll choose(int n, int k) {
    if (psum[n]-psum[k]-psum[n-k] > 0) return 0LL;
    return (fact[n]*invf[k] % P) * invf[n-k] % P;
}

// sieve and store ans
int jmp[MN];
ll cnt[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> P;
    for (auto i = 1; i <= N; i++)
        cin >> A[i];

    // compute factorials
    fact[0] = 1;
    for (auto i = 1; i <= N; i++) {
        fact[i] = i;
        psum[i] = psum[i-1];
        while (fact[i]%P == 0) {
            fact[i] /= P;
            psum[i]++;
        }
        fact[i] *= fact[i-1];
        fact[i] %= P;
    }
    invf[N] = inv(fact[N], P);
    for (auto i = N-1; i >= 0; i--) {
        ll v = i+1;
        while (v%P == 0) v /= P;
        invf[i] = invf[i+1]*v % P;
    }

    // sieve
    iota(jmp, jmp+MN, 0);
    for (auto i = 2; i < MN; i++) {
        if (jmp[i] == i) {
            for (auto j = i+i; j < MN; j += i)
                jmp[j] = i;
        }
    }

    // get power of each prime
    for (auto i = 1; i <= N; i++) {
        int co = choose(N-1, i-1);
        for (auto c = A[i]; c != 1; c /= jmp[c])
            cnt[jmp[c]] += co;
    }
    // get ans
    ll ans = 1;
    for (auto i = 1; i < MN; i++)
        if (cnt[i] % P)
            ans = ans*fpow(i, cnt[i]%P) % MOD;
    cout << (ans) << '\n';

    return 0;
}