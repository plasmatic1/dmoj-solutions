// ./dmopc-20-contest-7-p4-mimi-and-carrots-ii.yml
#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt"

// I've fallen and can't get back up
// Help me
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
// template <typename T> using opt_ref = optional<reference_wrapper<T>>; // for some templates
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

const int MN = 2e5 + 10, LG = 20, BS = 650;
int N, Q,
    A[MN];
vector<int> g[MN];

// LCA
int tb[LG][2*MN], fst[MN], dep[MN], par[MN], ctrLca = 0;
vector<int> ord;
void dfs(int c, int p) {
    par[c] = p;
    tb[0][++ctrLca] = c;
    fst[c] = ctrLca;
    ord.pb(c);
    for (auto to : g[c]) {
        if (to != p) {
            dep[to] = dep[c]+1;
            dfs(to, c);
            tb[0][++ctrLca] = c;
        }
    }
}
bool byDep(const int a, const int b) { return dep[a] < dep[b]; };
int lca(int a, int b) {
    a = fst[a]; b = fst[b];
    if (a > b) swap(a, b);
    int bit = __lg(b-a+1);
    return min(tb[bit][a], tb[bit][b-(1<<bit)+1], byDep);
}
int dis(int a, int b) { return dep[a]+dep[b]-2*dep[lca(a, b)]; }
int disToPath(int a, int b, int u) { return (dis(a, u) + dis(u, b) - dis(a, b)) / 2; }

// sqrt stuff
int psum[MN];
int qpath(int u, int v) {
    int res = psum[u] + psum[v], lv = lca(u, v);
    if (par[lv] != -1) res -= 2*psum[par[lv]];
    res -= psum[lv] - psum[par[lv]];
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    for (auto i = 0; i < N-1; i++) {
        int a, b; cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }

    dfs(1, 0);
    for (auto i = 1; i < LG; i++) {
        int jmp = 1<<(i-1), end = ctrLca-(1<<i)+1;
        for (auto j = 1; j <= end; j++) {
            tb[i][j] = min(tb[i-1][j], tb[i-1][j+jmp], byDep);
        }
    }

    vector<int> upd;
    for (auto i = 0; i < Q; i++) {
        int T; cin >> T;
        if (T == 1) { 
            int x; cin >> x;
            upd.pb(x);
        }
        else {
            int u, v; cin >> u >> v;
            // sum all, and then subtract triple counted ones
            int ans = qpath(u, v) + A[u] + A[v];

            for (auto x : upd) {
                int co = (A[x] ^ 1) - A[x];
                A[x] ^= 1;
                if (disToPath(u, v, x) <= 1)
                    ans += co;
            }
            cout << (ans) << '\n';

            // clean up
            for (auto x : upd) A[x] ^= 1;
        }

        if (SZ(upd) > BS) {
            for (auto x : upd)
                A[x] ^= 1;

            fill(psum, psum+MN, 0);
            for (auto i = 1; i <= N; i++) {
                if (A[i]) {
                    psum[i]--;
                    for (auto to : g[i])
                        psum[to]++;
                }
            }
            for (auto i : ord)
                psum[i] += psum[par[i]];

            upd.clear();
        }
    }

}