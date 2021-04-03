// ./back-to-school-19-fft-fun.yml
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
using ll = long long; using ull = unsigned long long; 
using ld = long double;
// using ld = double;
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

using T = tuple<ld, int, int>;

/*
Some testing with the presumed worst case of

1
1000000000000000000 2 999999733

reveals that x,y<=293 in getcnt should be sufficient.  I put it here as 500 just in case.
Realistically, you want to make it as large as possible if you aren't sure.
*/
const int MP = 501;
const ll ALIM = 1e18+1;
int X, Y;
ll N,
   cnt[MP][MP];

ll comb(ll init, ll a, ll b) {
    auto p = __int128(a) * b;
    if (p >= ALIM) return ALIM;
    return min(ALIM, init + ll(p));
}

ll getcnt(int x, int y) {
    if (cnt[x][y] != -1) return cnt[x][y];
    cnt[x][y] = 0;
    for (auto i = 0; i <= x; i++) {
        for (auto j = 0; j <= y; j++) {
            if (i == x && j == y) continue;
            int a = x-i, b = y-j;
            if (MP*i+j > MP*a+b) continue;
            if (a == i && b == j) {
                getcnt(i, j);
                auto p = cnt[x][y] + __int128(cnt[i][j]) * (cnt[i][j]-1) / 2;
                if (p > ALIM) cnt[x][y] = ALIM;
                else cnt[x][y] = p;
                continue;
            }
            cnt[x][y] = comb(cnt[x][y], getcnt(i, j), getcnt(a, b));
            if (cnt[x][y] == ALIM) break;
        }
    }
    return cnt[x][y];
}

void solve() {
    cin >> (N) >> (X) >> (Y);
    N += 2; ld lx = log(X), ly = log(Y);

    priority_queue<T, vector<T>, greater<T>> pq; 
    set<pii> use;

    auto push = [&] (int x, int y) {
        if (!use.count({x, y})) {
            pq.emplace(x * lx + y * ly, x, y);
            use.emplace(x, y);
        }
    };
    push(1, 0); push(0, 1);

    ll prod = 1;
    while (!pq.empty()) {
        auto [_, x, y] = pq.top(); pq.pop();
        getcnt(x, y); assert(x < MP && y < MP);
        if (!cnt[x][y]) continue;

        ll val = fix(fpow(X, x) * fpow(Y, y));
        prod = fix(prod * fpow(val, min(N, cnt[x][y])));
        N -= cnt[x][y];
        if (N <= 0) {
            cout << prod << '\n';
            return;
        }

        push(x+1, y);
        push(x, y+1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    memset(cnt, -1, sizeof cnt);
    cnt[0][1] = cnt[1][0] = 1LL;

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}