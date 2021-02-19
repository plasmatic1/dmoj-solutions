// ./wesleys-anger-contest-6-problem-4-tbd.yml
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

const ll MOD = 998244353;
ll fix(ll &&x) { x %= MOD; if (x < 0) x += MOD; return x; }
ll fix(ll &x) { x %= MOD; if (x < 0) x += MOD; return x; }
ll fpow(ll x, ll y, ll mod = MOD) {
    if (!y) return 1LL;
    return fpow(x * x % mod, y >> 1, mod) * ((y & 1) ? x : 1LL) % mod;
}
ll inv(ll x, ll mod = MOD) { return fpow(x, mod - 2, mod); }

struct wesley {
    ll m[4][4];
    wesley() { memset(m, 0, sizeof m); }
    wesley mul(wesley r) {
        wesley res;
        for (auto i = 0; i < 4; i++) {
            for (auto j = 0; j < 4; j++) {
                for (auto k = 0; k < 4; k++) res.m[i][j] += m[i][k] * r.m[k][j];
                fix(res.m[i][j]);
            }
        }
        return res;
    }
    void pr() {
        for (auto i = 0; i < 4; i++) {
            cout<<"m[i]=["; for(int __i=0; __i<(4); __i++)cout<<m[i][__i]<<", "; cout<<"], ";cout << endl; // db A:4:m[i]
        }
    }
};

const int MN = 2e5 + 1;
int N, K;
string s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (K) >> (s);
    wesley carol;
    for (auto i = 0; i < 4; i++) carol.m[i][i] = 1;
    for (auto c : s) {
        wesley besley;
        for (auto i = 0; i < 4; i++) besley.m[i][i] = 1;
        if (c == 'W') besley.m[1][0] = 1;
        else if (c == 'A') besley.m[2][1] = 1;
        else if (c == 'C') besley.m[3][2] = 1;
        carol = besley.mul(carol);
    }
    wesley cute;
    for (auto i = 0; i < 4; i++) cute.m[i][i] = 1;
    for (auto i = 0; i < 19; i++) {
        if ((K >> i) & 1)
            cute = carol.mul(cute);
        carol = carol.mul(carol);
    }
    cout << (cute.m[3][0]) << '\n';

    return 0;
}