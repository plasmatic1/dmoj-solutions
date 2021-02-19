// ./dmopc-20-contest-3-p3-a-ring-of-buckets.yml
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

const int LG = 30;

// compute 1+B+B^2+...+B^(k-1)
ll compute(ll B, int k) {
    ll tb[LG]; memset(tb, 0, sizeof tb);
    tb[0] = B;

    // cout<<"[compute]: "; cout<<"B="<<(B)<<", "; cout<<"k="<<(k)<<", "; cout << endl; // db l:compute,B,k
    for (auto i = 1; i < LG; i++) {
        tb[i] = tb[i-1] + tb[i-1]*fpow(B, 1 << (i-1));
        fix(tb[i]);
    }
    ll res = 0;
    for (auto i = LG-1; i >= 0; i--) {
        int pow = 1<<i;
        if (((k-1) >> i) & 1) {
            res = fix(res * fpow(B, pow) + tb[i]);
        }
    }
    res = fix(res+1);
    // cout<<"res="<<(res)<<", "; cout << endl; // db res
    return res;
}

ll N, M, K, B;

void solve() {
    cin >> (N) >> (M) >> (K) >> (B);

    if ((N * M) % (K + 2) != 0) {
        cout << (-1) << '\n';
        return;
    }
    ll pours = (N*M) / (K+2);

    if (K == 1 && N % 3 == 0) {
        ll res = fix(compute(fpow(B, 3), N/3) * fpow(B, 2));
        res *= pours / (N / 3);
        fix(res);
        cout << (res) << '\n';
        return;
    }
    else if (K == 2 && N % 2 == 0 && M % 2 == 0) {
        ll res = fix(compute(fpow(B, 2), N/2) * B);
        res *= pours / (N / 2);
        fix(res);
        cout << (res) << '\n';
        return;
    }

    if (pours % N != 0) {
        cout << (-1) << '\n';
        return;
    }

    ll poursPer = pours / N, totPer = poursPer * (K + 2);
    if (totPer != M) {
        cout << (-1) << '\n';
        return;
    }

    ll res = compute(B, N);
    res *= pours / N;
    fix(res);
    cout << (res) << '\n';
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