// ./baltic-oi-17-p1-political-development.yml
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

const int MN = 5e4 + 1, MK = 10;
int N, variableThatWillBeUnused,
    deg[MN];
unordered_set<int> g[MN];
set<pii> pq;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (variableThatWillBeUnused);
    for (auto i = 0; i < N; i++) {
        int n;
        cin >> n;
        for (auto j = 0; j < n; j++) {
            int x;
            cin >> x;
            g[i].insert(x);
            deg[x]++;
        }
    }

    for (auto i = 0; i < N; i++)
        pq.emplace(deg[i], i);

    int ans = 0;
    while (!pq.empty()) {
        auto c = *pq.begin(); pq.erase(pq.begin());
        vector<int> vv(all(g[c.sn])); vv.pb(c.sn);
        int sz = SZ(vv);
        vector<vector<bool>> adj(sz, vector<bool>(sz));
        int ic = 0, jc = 0;
        for (auto x : vv) {
            adj[ic][ic] = true;
            for (auto y : vv) {
                if (x == y) { jc++; continue; }
                adj[ic][jc] = g[x].count(y);
                jc++;
            }
            ic++;
            jc = 0;
        }
        // cout<<"c.sn="<<(c.sn)<<", "; cout << "vv=["; for (auto x:vv)cout<<x<<", "; cout<<"], "; cout << endl; // db c.sn,I:vv
        for (auto i = 0; i < (1<<sz); i++) {
            bool good = true;
            vector<int> cur;
            for (auto j = 0; j < sz; j++)
                if ((i >> j) & 1)
                    cur.pb(j);
            // cout<<"i="<<(bitset<5>(i))<<", "; cout << "cur=["; for (auto x:cur)cout<<x<<", "; cout<<"], "; cout << endl; // db b:5:i,I:cur
            for (auto x : cur) {
                for (auto y : cur) {
                    if (!adj[x][y]) {
                        // cout<<"x="<<(x)<<", "; cout<<"y="<<(y)<<", "; cout<<"adj[x][y]="<<(adj[x][y])<<", "; cout << endl; // db x,y,adj[x][y]
                        good = false;
                        break;
                    }
                }
                if (!good) break;
            }
            if (good)
                maxa(ans, __builtin_popcount(i));
        }
        for (int to : g[c.sn]) {
            int old = deg[to]--;
            pq.erase(mpr(old, to));
            pq.emplace(deg[to], to);
            g[to].erase(c.sn);
        }
        g[c.sn].clear();
        // for (auto i = 0; i < N; i++) {
        //     cout<<"i="<<(i)<<", "; cout << "g[i]=["; for (auto x:g[i])cout<<x<<", "; cout<<"], "; cout << endl; // db i,I:g[i]
        // }
    }
    cout << (ans) << '\n';

    return 0;
}