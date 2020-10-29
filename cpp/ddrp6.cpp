// ./double-doors-regional-p6-tudor-learns-more-ddr.yml
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

// it's ok, I'm disappointed in myself too
const ll MOD = 1e9 + 7;
ll fix(ll &&x) { x %= MOD; if (x < 0) x += MOD; return x; }
ll fix(ll &x) { x %= MOD; if (x < 0) x += MOD; return x; }
ll fpow(ll x, ll y, ll mod = MOD) {
    if (!y) return 1LL;
    return fpow(x * x % mod, y >> 1, mod) * ((y & 1) ? x : 1LL) % mod;
}
ll inv(ll x, ll mod = MOD) { return fpow(x, mod - 2, mod); }

// L,D,R,U (0,1,2,3)
// L,U,R,D (0,3,2,1)
int SEQ[2][4] {
    {0, 1, 2, 3},
    {0, 3, 2, 1},
};

const int MN = 65, MPOS = 256;
ll N,
   tr[MN][MN], res[MN];
bool good[MPOS];

void mul(ll a[MN][MN], ll b[MN][MN]) {
    static ll res[MN][MN];
    for (auto i = 0; i < MN; i++) {
        for (auto j = 0; j < MN; j++) {
            res[i][j] = 0;
            for (auto k = 0; k < MN; k++)
                res[i][j] += fix(a[i][k] * b[k][j]);
            fix(res[i][j]);
        }
    }
    for (auto i = 0; i < MN; i++)
        for (auto j = 0; j < MN; j++)
            a[i][j] = res[i][j];
}
void mulv(ll a[MN], ll b[MN][MN]) {
    static ll res[MN];
    for (auto i = 0; i < MN; i++) {
        res[i] = 0;
        for (auto j = 0; j < MN; j++)
            res[i] += fix(b[i][j] * a[j]);
        fix(res[i]);
    }
    copy(res, res + MN, a);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    if (N < 4) {
        cout << (fpow(4, N)) << '\n';
        return 0;
    }

    // get good seqs
    for (auto i = 0; i < 2; i++) {
        for (auto j = 0; j < 4; j++) {
            int enc = 0;
            for (auto k = 0; k < 4; k++)
                enc = (enc << 2) | SEQ[i][k];
            good[enc] = true;
            rotate(SEQ[i], SEQ[i] + 1, SEQ[i] + 4);
        }
    }

    // init transition and cpow matrices
    for (auto i = 0; i < 64; i++) {
        int two = (i & 15) << 2;
        for (auto j = 0; j < 4; j++) {
            if (good[(i << 2) | j]) tr[64][i]++;
            else tr[two | j][i]++;
        }
    }
    tr[64][64] = 4;
    fill(res, res + 64, 1);

    // multiply and get answer
    for (auto i = 0; i < 60; i++) {
        if (((N - 4) >> i) & 1)
            mulv(res, tr);
        mul(tr, tr);
    }

    ll ans = res[64] * 4;
    for (auto i = 0; i < MPOS; i++) 
        if (good[i])
            ans += res[i >> 2];
    fix(ans);
    cout << (fix(fpow(4, N) - ans)) << '\n';

    return 0;
}