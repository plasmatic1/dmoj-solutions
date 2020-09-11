// boi-2019-p3-alpine-valley.yml
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

struct Ed {
    int v, w;
};

const int MN = 1e5 + 1, LG = 17;
int N, Q, S, E,
    A[MN], W[MN], B[MN], dep[MN];
vector<Ed> g[MN];

ll dp[MN], dis[MN], tb[LG][MN], par[LG][MN];
bool shop[MN];

void dfs(int c, int p, ll cdis) {
    dep[c] = p == -1 ? 0 : dep[p] + 1; dis[c] = cdis; par[0][c] = p;
    dp[c] = LLINF;
    for (auto to : g[c]) {
        if (to.v != p) {
            dfs(to.v, c, cdis + to.w);
            mina(dp[c], dp[to.v] + to.w);
        }
    }

    if (shop[c]) dp[c] = 0;
    tb[0][c] = dp[c] - cdis;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (S) >> (Q) >> (E);
    for (auto i = 0; i < N-1; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        g[a].pb({b, w});
        g[b].pb({a, w});
        A[i] = a;
        B[i] = b;
        W[i] = w;
    }
    for (auto i = 0; i < S; i++) {
        int k;
        cin >> k;
        shop[k] = true;
    }

    // Build binary lift
    dfs(E, -1, 0);
    for (auto i = 1; i < LG; i++) {
        for (auto j = 1; j <= N; j++) {
            int pp = par[i - 1][j];
            par[i][j] = pp == -1 ? -1 : par[i - 1][pp];
            tb[i][j] = min(tb[i - 1][j], pp == -1 ? LLINF : tb[i - 1][pp]);
        }
    }

    // Answer queries
    while (Q--) {
        int i, r;
        cin >> i >> r; i--;

        int bt = dep[A[i]] > dep[B[i]] ? A[i] : B[i], c = r; int delta = dep[c] - dep[bt];
        if (delta < 0) {
            cout << ("escaped") << '\n';
            continue;
        }

        for (auto i = 0; i < LG; i++)
            if ((delta >> i) & 1)
                c = par[i][c];

        if (c == bt) {
            ll bestAns = LLINF;
            c = r;
            for (auto i = 0; i < LG; i++) {
                if ((delta >> i) & 1) {
                    mina(bestAns, tb[i][c]);
                    c = par[i][c];
                }
            }
            mina(bestAns, tb[0][c]);

            bestAns += dis[r];
            cout << (bestAns >= LLINF ? "oo" : to_string(bestAns)) << '\n';
        }
        else 
            cout << ("escaped") << '\n';
    }

    return 0;
}