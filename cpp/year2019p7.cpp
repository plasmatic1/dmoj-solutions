// ./the-order-of-the-fox.yml
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

const ll MOD = 1e9 + 7;
const int MN = 3e5 + 1;
int N, M,
    A[MN], B[MN], deg[MN], tri[MN], mark[MN];
vector<pii> g[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M);
    for (auto i = 0; i < M; i++) {
        cin >> (A[i]) >> (B[i]);
        deg[A[i]]++;
        deg[B[i]]++;
    }
    for (auto i = 0; i < M; i++) {
        int a = A[i], b = B[i];
        if (deg[a] > deg[b]) swap(a, b);
        else if (deg[a] == deg[b] && a > b)
            swap(a, b);
        g[a].eb(b, i);
    }

    memset(mark, -1, sizeof mark);
    for (auto i = 1; i <= N; i++) {
        for (auto to : g[i]) mark[to.fs] = to.sn;
        for (auto to : g[i]) {
            for (auto to2 : g[to.fs]) {
                if (mark[to2.fs] != -1) {
                    tri[to.sn]++;
                    tri[to2.sn]++;
                    tri[mark[to2.fs]]++;
                }
            }
        }
        for (auto to : g[i]) mark[to.fs] = -1;
    }

    ll ans = 0;
    for (auto i = 1; i <= N; i++) {
        for (auto to : g[i]) mark[to.fs] = to.sn;
        for (auto to : g[i]) {
            for (auto to2 : g[to.fs]) {
                if (mark[to2.fs] != -1) {
                    ll ad = deg[i], bd = deg[to.fs], cd = deg[to2.fs];
                    // triangle edges
                    ad -= 2;
                    bd -= 2;
                    cd -= 2;

                    ans += (ad * bd - tri[to.sn] + 1) % MOD;
                    ans += (bd * cd - tri[to2.sn] + 1) % MOD;
                    ans += (ad * cd - tri[mark[to2.fs]] + 1) % MOD;

                    ans %= MOD;
                }
            }
        }
        for (auto to : g[i]) mark[to.fs] = -1;
    }
    cout << (ans) << '\n';

    return 0;
}