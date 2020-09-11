// ./cco-19-p2-sirtet.yml
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

struct Ed {
    int v, w;
    bool operator<(const Ed &o) const {
        return w > o.w; 
    }
};

const int MN = 1e6 + 1;
int N, M, cN;
string grid[MN];
vector<pii> group[MN];

// first dfs
vector<vector<bool>> vis;
vector<vector<int>> groupNo;
vector<pii> found;
void dfs(int x, int y) {
    if (x < 0 || x >= N || y < 0 || y >= M || grid[x][y] == '.' || vis[x][y]) return;
    vis[x][y] = true;
    found.eb(x, y);
    dfs(x + 1, y); dfs(x - 1, y);
    dfs(x, y + 1); dfs(x, y - 1);
}

// dijkstra and building graph
int dis[MN];
vector<Ed> g[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M);
    for (auto i = 0; i < N; i++)
        cin >> (grid[i]);

    // DFS for groups
    cN = 0;
    vis.assign(N, vector<bool>(M));
    groupNo.assign(N, vector<int>(M, -1));
    for (auto i = 0; i < N; i++) {
        for (auto j = 0; j < M; j++) {
            if (!vis[i][j] && grid[i][j] == '#') {
                found.clear();
                dfs(i, j);
                for (auto &p : found) groupNo[p.fs][p.sn] = cN;
                group[cN++] = found;
            }
        }
    }

    // Build graph
    vector<pii> pre(M, mpr(N, N * M));
    for (auto i = N-1; i >= 0; i--) {
        for (auto j = 0; j < M; j++) {
            if (groupNo[i][j] != -1) {
                auto down = pre[j];
                g[down.sn].pb({groupNo[i][j], down.fs - i - 1});
                pre[j] = mpr(i, groupNo[i][j]);
            }
        }
    }

    // Dijkstra
    priority_queue<Ed> pq;
    memset(dis, 0x3f, sizeof dis);
    dis[N * M] = 0; pq.push({N * M, 0});
    while (!pq.empty()) {
        auto c = pq.top(); pq.pop();
        if (c.w > dis[c.v]) continue;
        for (auto to : g[c.v]) {
            int alt = c.w + to.w;
            if (alt < dis[to.v]) {
                dis[to.v] = alt;
                pq.push({to.v, alt});
            }
        }
    }

    // Reconstruct answer
    vector<string> ans(N, string(M, '.'));
    for (auto i = 0; i < cN; i++) {
        for (auto p : group[i]) {
            ans[p.fs + dis[i]][p.sn] = '#';
        }
    }

    // Print ans
    for (auto &r : ans)
        cout << (r) << '\n';

    return 0;
}