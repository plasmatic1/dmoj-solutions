// apio-11-p1-table-coloring.yml
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

const ll MOD = 1e9;
ll madd(ll a, ll b, ll mod = MOD) { return (a + b) % mod; }
ll msub(ll a, ll b, ll mod = MOD) { return (a - b + mod) % mod; }
ll mmul(ll a, ll b, ll mod = MOD) { return (a * b) % mod; }
ll fpow(ll x, ll y, ll mod = MOD) {
    if (!y) return 1LL;
    return mmul(fpow(mmul(x, x, mod), y >> 1, mod), (y & 1) ? x : 1LL, mod);
}

/*
Red=1, Blue=0
Observation: We can translate the problem to for every 2x2 square, the XOR must be 1
Observation: If we fix the first row and column, we can compute the rest of the grid
Observation: Look at the patterns created
*/

struct Ed {
    int c, b, w;
};

const int MN = 1e5 + 1, MNODE = MN * 2;
int N, M, K, setOrigin = -1,
    force[MNODE];
vector<Ed> edges;
vector<pii> g[MNODE];

bool bad = false, homeInv = false;
int nDiff = 0, nSame = 0,
    clr[MNODE];
void dfs(int c, int cclr) {
    clr[c] = cclr;
    if (force[c] != -1) {
        if (cclr != force[c]) nDiff++;
        else nSame++;
    }
    for (auto to : g[c]) {
        bool nxt = cclr ^ to.second ^ homeInv;
        if (clr[to.first] == -1) {
            dfs(to.first, nxt); } 
        else if (clr[to.first] != nxt)
            bad = true;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M) >> (K);

    memset(force, -1, sizeof force);
    for (auto i = 0; i < K; i++) {
        int x, y, clr;
        cin >> x >> y >> clr;

        if (x == 1 && y == 1)
            setOrigin = clr;
        else if (x == 1) {
            force[y + N] = clr; }
        else if (y == 1) {
            force[x] = clr; }
        else {
            bool tclr = clr ^ (x % 2 + y % 2 == 0);
            edges.pb({x, y + N, tclr});
            g[x].emplace_back(y + N, tclr);
            g[y + N].emplace_back(x, tclr);
        }
    }

    ll ans = 0;
    for (int home = 0; home < 2; home++) {
        if (setOrigin != -1 && setOrigin != home) continue;

        ll cans = 1;
        bad = false; homeInv = home; memset(clr, -1, sizeof clr);
        for (auto i = 2; i <= N + M; i++) {
            if (i == N + 1) continue; // also (1, 1)
            if (clr[i] == -1) {
                nDiff = 0; nSame = 0;
                dfs(i, 0);
                if (!(nSame || nDiff))
                    cans = mmul(cans, 2);
                bad |= nSame && nDiff;
            }
        }
        if (bad) cans = 0;

        ans = madd(ans, cans);
    }

    cout << (ans) << '\n';

    return 0;
}