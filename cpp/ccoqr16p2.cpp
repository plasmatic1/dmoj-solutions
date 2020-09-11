// ./ccoqr-16-through-a-maze-darkly.yml
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
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 1e5 + 1, MNODE = 5e5 + 1;
int N, Q;

// node
int nodeCtr;
int getNode() { return ++nodeCtr; }

vector<int> to[MN], nodeId[MN];
map<int, int> idMap[MN];

// dfs and graph stuff
int cycleId[MNODE], g[MNODE];
bool vis[MNODE];
vector<vector<int>> cycles;
vector<map<int, int>> cyclePosOfNode;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    for (auto i = 1; i <= N; i++) {
        int n;
        cin >> n;
        for (auto j = 0; j < n; j++) {
            int x;
            cin >> x;
            to[i].pb(x);
        }
    }

    // build auxillary graph (Node #, IDX of previous corridor to enter (Node #))
    for (auto i = 1; i <= N; i++) {
        for (auto j = 0; j < SZ(to[i]); j++)
            idMap[i][to[i][j]] = j;
        nodeId[i].resize(SZ(to[i]));
        for (auto &x : nodeId[i])
            x = getNode();
    }
    for (auto i = 1; i <= N; i++) {
        int sz = SZ(to[i]);
        for (auto j = 0; j < sz; j++) {
            int pathId = (j - 1 + sz) % sz, nxt = to[i][pathId];
            g[nodeId[i][j]] = nodeId[nxt][idMap[nxt][i]];
        }
    }

    // dfs on cycles (graph is functional, problem statement implies only cycles)
    for (auto i = 1; i <= nodeCtr; i++) {
        if (!vis[i]) {
            int c = i, len = 0;
            vector<int> see;
            while (!vis[c]) {
                vis[c] = true;
                see.pb(c);
                len++;

                c = g[c];
            }

            int ptr = SZ(cycles), cptr = 0;
            cycles.pb(see);
            cyclePosOfNode.pb(map<int, int>());
            for (auto &x : see) {
                cycleId[x] = ptr;
                cyclePosOfNode[ptr][x] = cptr;
                cptr++;
            }
        }
    }

    // Answer queries
    cin >> (Q);
    while (Q--) {
        int x;
        cin >> x;

        int ans = -INF;
        map<int, vector<int>> curCycles;
        for (auto &x : nodeId[x]) {
            curCycles[cycleId[x]].pb(cyclePosOfNode[cycleId[x]][x]); }
        for (auto &p : curCycles) {
            vector<int> seq = p.sn;
            int csz = SZ(cycles[p.fs]);
            for (auto &x : p.sn)
                seq.pb(x + csz);
            sort(all(seq));

            for (auto i = 1; i < SZ(seq); i++)
                maxa(ans, seq[i] - seq[i - 1]);
        }
        cout << (ans) << '\n';
    }

    return 0;
}