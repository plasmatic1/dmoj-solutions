// ioi-19-p2-split-the-attractions.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define pb push_back
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
template <typename C> int SZ(C &v) { return v.size(); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 1e5 + 1;
int N, M,
    S[3], revPerm[3];
vector<int> g[MN], back[MN];

// Setup dfs and initial preprocessing
set<int> good[MN];
int sz[MN], ord[MN], par[MN];
bool dfsInit(int c, int p) {
    static int cord = 1;
    if (ord[c] != -1) return false;
    sz[c] = 1; ord[c] = cord++; par[c] = p;
    for (int to : g[c]) {
        if (dfsInit(to, c)) {
            sz[c] += sz[to];
            good[c].insert(to);
        }
        else if (to != p) {
            back[c].pb(to); }
    }
    good[c].insert(p);
    return true;
}

/*
Cases: 
- found final child and csz-SZ(u) < A.  In this case, csz <= 2A and thus osz >= B
- did not find final child and both csz, osz >= A.  Since they're connected components that contain all the nodes and are both >= A, one of them must also be >= B.
- osz < A.  We're done for :(
*/

// dfs #2
vector<int> ans;
int done = 0; // 0->not done, 1->done (good)
bool vis[MN], instk[MN];

bool block[MN];

// Uses tree edges only
// Assigns final answer
void dfsAssign(int c, int p, bool stopAtBlock, int assignTo, int &left) {
    if (c == -1) return;
    if (block[c] && stopAtBlock) return;
    if (left) {
        ans[c] = assignTo;
        left--;
    }
    for (int to : g[c]) {
        if (good[c].count(to) && to != p) {
            dfsAssign(to, c, stopAtBlock, assignTo, left);
        }
    }
}

// main dfs
void dfs(int c) {
    if (done || vis[c]) return;
    vis[c] = true;
    instk[c] = true;

    // Deteremine if answer is possible
    vector<int> swapChild;
    int csz = sz[c], osz = N - csz;
    for (int to : g[c]) {
        if (sz[c] >= S[0]) {
            if (good[c].count(to)) {
                dfs(to);
                if (csz - sz[to] >= S[0]) {
                    bool can = false;
                    for (int bk : back[to]) {
                        if (instk[bk] && bk != c) // goes back to a parent of c
                            can = true;
                    }
                    if (can) {
                        csz -= sz[to];
                        osz += sz[to];
                        swapChild.pb(to);
                    }
                }
            }
        }
    }

    // Set ans array if exists
    if (done) return;
    if (sz[c] >= S[0]) {
        for (auto x : swapChild) block[x] = true;

        if (csz >= S[0] && osz >= S[1]) {
            dfsAssign(c, par[c], true, 1, S[0]);
            dfsAssign(par[c], c, false, 2, S[1]);
            for (auto x : swapChild) dfsAssign(x, par[x], false, 2, S[1]);
            done = true;
        }
        else if (csz >= S[1] && osz >= S[0]) {
            dfsAssign(c, par[c], true, 2, S[1]);
            dfsAssign(par[c], c, false, 1, S[0]);
            for (auto x : swapChild) dfsAssign(x, par[x], false, 1, S[0]);
            done = true;
        }

        for (auto x : swapChild) block[x] = false;
    }

    instk[c] = false; 
}

vector<int> find_split(int N0, int A0, int B0, int C0, vector<int> p, vector<int> q) {
    // Input
    N = N0; M = SZ(p);
    ans.resize(N);
    for (auto i = 0; i < M; i++) {
        g[p[i]].pb(q[i]);
        g[q[i]].pb(p[i]);
    }

    // Setup A<=B<=C
    vector<pii> sizes{{A0, 0}, {B0, 1}, {C0, 2}};
    sort(all(sizes));
    for (auto i = 0; i < 3; i++) {
        S[i] = sizes[i].first;
        revPerm[i] = sizes[i].second + 1;
    }

    // Do DFS
    fill(ord, ord + N, -1);
    dfsInit(0, -1);
    fill(vis, vis + N, false);
    dfs(0);
    if (!done) return ans;

    // Transform answer properly
    for (auto &x : ans) {
        if (x) x--;
        else x = 2;
        x = revPerm[x];
    }
    return ans;
}

#ifdef LOCAL
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int id;
    cin >> id;
    
    vector<int> res;
    if (id == 0) {
        res = find_split(9, 4, 2, 3, {0, 0, 0, 0, 0, 0, 1, 3, 4, 5}, {1, 2, 3, 4, 6, 8, 7, 7, 5, 6}); }
    else if (id == 1) {
        res = find_split(6, 2, 2, 2, {0, 0, 0, 0, 0}, {1, 2, 3, 4, 5}); }

    cout<<"id="<<(id)<<", "; cout << endl; // db id
    cout << "res=["; for (auto x:res)cout<<x<<", "; cout<<"], "; cout << endl; // db I:res

    return 0;
}
#endif