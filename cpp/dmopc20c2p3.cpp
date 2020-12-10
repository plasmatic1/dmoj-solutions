// ./dmopc-20-contest-2-p3-roadrollification.yml
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

const int MN = 2e5 + 1;
int N,
    A[MN], B[MN];
ll val[MN], sumStart[MN], sumEnd[MN];
vector<int> g[MN], rg[MN];

bool vis[MN];
ll dfs(int c, int p, vector<int> g[MN], ll sum[MN]) {
    if (vis[c]) return sum[c];
    vis[c] = true;
    sum[c] = val[c];
    for (auto to : g[c])
        if (to != p)
            sum[c] += dfs(to, c, g, sum);
    return sum[c];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    for (auto i = 1; i <= N; i++) cin >> val[i];
    for (auto i = 0; i < N-1; i++) {
        cin >> (A[i]) >> (B[i]);
        g[A[i]].pb(B[i]);
        rg[B[i]].pb(A[i]);
    }

    for (auto i = 1; i <= N; i++)
        if (!vis[i])
            dfs(i, -1, g, sumStart);
    memset(vis, false, sizeof vis);
    for (auto i = 1; i <= N; i++)
        if (!vis[i])
            dfs(i, -1, rg, sumEnd);

    // cout<<"(sumStart+1)=["; for(int __i=0; __i<(N); __i++)cout<<(sumStart+1)[__i]<<", "; cout<<"], ";cout << endl; // db A:N:(sumStart+1)
    // cout<<"(sumEnd+1)=["; for(int __i=0; __i<(N); __i++)cout<<(sumEnd+1)[__i]<<", "; cout<<"], ";cout << endl; // db A:N:(sumEnd+1)

    // first part right
    ll add = 0, ans = 0;
    for (auto i = 1; i <= N; i++)
        ans += val[i] * sumStart[i] - val[i];
    // cout<<"ans="<<(ans)<<", "; cout << endl; // db ans
    for (auto i = 0; i < N-1; i++)
        maxa(add, (sumEnd[B[i]] - sumEnd[A[i]]) * (sumStart[A[i]] - sumStart[B[i]]));
    cout << (ans + add) << '\n';

    return 0;
}