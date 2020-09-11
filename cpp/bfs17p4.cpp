// ./back-from-summer-17-p4-pair-programming.yml
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

const int MN = 1e5 + 1;
int N;
// dp[i][j] -> (min, max) number of errors assuming that line i is WA/AC
pii dp[MN][2]; // 0->WA, 1->AC
vector<int> g[MN];
bool rt[MN];
string V[MN];

void dfs(int c) {
    dp[c][0] = mpr(1, 1); dp[c][1] = mpr(0, 0);
    for (int to : g[c]) {
        dfs(to);

        int mn = INF, mx = -INF;
        if (V[to] != "WA") mina(mn, dp[to][0].fs), maxa(mx, dp[to][0].sn); // inverse for WA
        if (V[to] != "AC") mina(mn, dp[to][1].fs), maxa(mx, dp[to][1].sn);
        dp[c][0].fs += mn; dp[c][0].sn += mx;

        mn = INF, mx = -INF;
        if (V[to] != "AC") mina(mn, dp[to][0].fs), maxa(mx, dp[to][0].sn);
        if (V[to] != "WA") mina(mn, dp[to][1].fs), maxa(mx, dp[to][1].sn);
        dp[c][1].fs += mn; dp[c][1].sn += mx;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);

    for (auto i = 1; i <= N; i++) {
        char T;
        cin >> T;
        if (T == 'C') {
            cin >> (V[i]);
            rt[i] = true;
        }
        else {
            int p;
            cin >> p >> V[i];
            g[p].pb(i);
        }
    }

    pii ans;
    for (auto i = 1; i <= N; i++) {
        if (rt[i]) {
            dfs(i);
            int mn = INF, mx = -INF;
            if (V[i] != "AC") mina(mn, dp[i][0].fs), maxa(mx, dp[i][0].sn);
            if (V[i] != "WA") mina(mn, dp[i][1].fs), maxa(mx, dp[i][1].sn);
            ans.fs += mn;
            ans.sn += mx;
        }
    }

    cout << (ans.fs) << ' ' << (ans.sn) << '\n';

    return 0;
}