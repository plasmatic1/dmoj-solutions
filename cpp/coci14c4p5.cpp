// ./coci-14-contest-4-5-sabor.yml
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

/*

Note: Input restricts nodes to have degree <=5

Observation: If a node is invalid (has more than 2 adjacents of the same colour), we can just flip its colour to make it valid.

Solution: Just keep updating nodes until the arrangement is valid.  How does this idea work?  I have no idea!

*/

const int MN = 2e5 + 1;
int N,
    deg[MN], clr[MN];
vector<int> g[MN];
bool inq[MN];

int cntSame(int x) {
    int res = 0;
    for (auto to : g[x]) res += clr[x] == clr[to];
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // input
    cin >> (N);
    for (auto _ = 0; _ < 5; _++) {
        int n;
        cin >> n;
        for (auto i = 0; i < n; i++) {
            int a, b;
            cin >> a >> b;
            g[a].pb(b);
            g[b].pb(a);
        }
    }
    for (auto i = 1; i <= N; i++) assert(SZ(g[i]) <= 5);

    // update nodes until arrangement is good
    deque<int> nxt;
    for (auto i = 1; i <= N; i++)
        if (SZ(g[i]) > 2)
            nxt.pb(i);
    while (!nxt.empty()) {
        int c = nxt.front(); nxt.pop_front();
        if (cntSame(c) <= 2) continue;
        clr[c] ^= 1; 
        for (int to : g[c])
            if (cntSame(to) > 2 && !inq[to])
                nxt.pb(to);
    }

    // print ans
    for (auto i = 1; i <= N; i++)
        cout << "AB"[clr[i]];
    cout << '\n';

    return 0;
}