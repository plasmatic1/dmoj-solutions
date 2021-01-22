// ./tle-15-p6-rock-paper-scissors.yml
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

const int MN = 5001;
int N, M, Q,
    dp[MN][MN];
vector<int> g[MN], cg[MN];

// tarj
int ctr = 0, cord = 0,
    ord[MN], low[MN], mp[MN], sz[MN];
vector<int> stk;
bool instk[MN];

void dfs(int c) {
    stk.pb(c); instk[c] = true;
    ord[c] = low[c] = ++cord;

    for (auto to : g[c]) {
        if (!ord[to]) {
            dfs(to);
            mina(low[c], low[to]);
        }
        else if (instk[to])
            mina(low[c], ord[to]);
    }

    if (low[c] == ord[c]) {
        int cno = ++ctr, u;
        do {
            u = stk.back(); stk.pop_back(); instk[u] = false;
            mp[u] = cno;
            sz[cno]++;
        } while (u != c);
    }
}

// topo
int indeg[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M) >> (Q);
    for (auto i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
    }
    for (auto i = 1; i <= N; i++)
        if (!ord[i])
            dfs(i);
    for (auto i = 1; i <= N; i++)
        for (auto j : g[i])
            if (mp[i] != mp[j])
                cg[mp[i]].pb(mp[j]);
    for (auto i = 1; i <= ctr; i++) {
        UNIQUE(cg[i]);
        for (auto to : cg[i])
            indeg[to]++;
    }
    queue<int> q;
    for (auto i = 1; i <= ctr; i++)
        if (!indeg[i])
            q.push(i);
    vector<int> ord;
    while (!q.empty()) {
        int c = q.front(); q.pop();
        ord.pb(c);
        for (auto to : cg[c])
            if (--indeg[to] == 0)
                q.push(to);
    }
    memset(dp, -0x3f, sizeof dp);
    for (auto i = 1; i <= ctr; i++) {
        dp[i][i] = 0;
        for (auto j : ord) {
            for (auto to : cg[j])
                maxa(dp[i][to], dp[i][j]+sz[to]);
        }
    }
    while (Q--) {
        int a, b;
        cin >> a >> b;

        int ta = mp[a], tb = mp[b], inva = dp[ta][tb] - sz[tb] < 0, invb = dp[tb][ta] - sz[ta] < 0;
        if (inva == invb)
            cout << ("Indeterminate") << '\n';
        else {
            if (inva) {
                swap(ta, tb);
                swap(a, b);
            }
            cout << (a) << ' ' << (dp[ta][tb]-sz[tb]) << '\n';
        }
    }

    return 0;
}