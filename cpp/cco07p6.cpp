// ./cco-07-p6-road-construction.yml
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

const int MN = 1001;
int N, M;

int low[MN], ord[MN], cord = 0;
vector<int> g[MN], auxg[MN];
set<pii> bridge;

void dfs(int c, int p = -1) {
    ord[c] = low[c] = ++cord;
    for (auto to : g[c]) {
        if (to != p) {
            if (!ord[to]) {
                dfs(to, c);
                mina(low[c], low[to]);
                if (low[to] > ord[c]) {
                    bridge.emplace(c, to);
                    bridge.emplace(to, c);
                }
            }
            else
                mina(low[c], ord[to]);
        }
    }
}

int cid[MN];
bool vis[MN];
void dfs2(int c, vector<int> &comp) {
    if (vis[c]) return;
    vis[c] = true;
    comp.pb(c);
    for (auto to : g[c])
        if (!bridge.count(mpr(c, to)))
            dfs2(to, comp);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M);

    for (auto i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }

    dfs(1);
    int ctr = 0;
    for (auto i = 1; i <= N; i++) {
        if (!vis[i]) {
            vector<int> comp;
            dfs2(i, comp);
            int cno = ++ctr;
            for (auto &x : comp) cid[x] = cno;
        }
    }

    for (auto i = 1; i <= N; i++) {
        for (auto &x : g[i])
            if (cid[i] != cid[x])
                auxg[cid[i]].pb(cid[x]);
        UNIQUE(auxg[i]);
    }

    int leafc = 0;
    for (auto i = 1; i <= ctr; i++)
        leafc += SZ(auxg[i]) == 1;
    cout << ((leafc+1) / 2) << '\n';

    return 0;
}