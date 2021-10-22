// ./p4-congcong-and-koko.yml
#include <bits/stdc++.h>
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
#if __cplusplus == 201703L // CPP17 only things
template <typename T> using opt_ref = optional<reference_wrapper<T>>; // for some templates
#endif
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

const int MN = 1001;
int N, M, C, K,
    dis[MN][MN], go[MN][MN];
vector<int> g[MN];
ld dp[MN][MN];

ld solve(int c, int k) {
    if (dis[c][k] == 0) return 0;
    else if (dis[c][k] <= 2) return 1;

    ld &ret = dp[c][k];
    if (ret != -1) return ret;

    ret = 1;
    int cNext = go[k][go[k][c]];
    ld p = 1. / (g[k].size() + 1);

    ret += p * solve(cNext, k);
    for (auto to : g[k])
        ret += p * solve(cNext, to);

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> C >> K;
    for (auto i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }
    for (auto i = 1; i <= N; i++)
        sort(all(g[i]));

    memset(dis, 0x3f, sizeof dis);
    for (auto i = 1; i <= N; i++) {
        queue<int> q;
        q.push(i); dis[i][i] = 0;
        while (!q.empty()) {
            int c = q.front(); q.pop();
            for (auto to : g[c]) {
                if (dis[i][c]+1 < dis[i][to]) {
                    dis[i][to] = dis[i][c]+1;
                    q.push(to);
                }
            }
        }

        for (auto j = 1; j <= N; j++)
            for (auto to : g[j])
                if (!go[i][j] || dis[i][go[i][j]] > dis[i][to])
                    go[i][j] = to;
    }

    for (auto i = 1; i <= N; i++)
        for (auto j = 1; j <= N; j++)
            dp[i][j] = -1;

    cout << fixed << setprecision(3) << solve(C, K) << '\n';

    return 0;
}