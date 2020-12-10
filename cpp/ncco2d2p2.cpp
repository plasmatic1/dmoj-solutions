// ./mock-cco-18-contest-2-problem-5-victors-triangles.yml
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
int N,
    clr[MN], tcnt[MN];
vector<int> g[MN];

// dsu
int dsu[MN];
int rt(int x) { return x == dsu[x] ? x : dsu[x] = rt(dsu[x]); }

// subtree and small/large merging stuff
bool good(int clr, int cnt) { return cnt == 0 || cnt == tcnt[clr]; }
struct subtObj {
    unordered_map<int, int> cnt;
    int sz = 0, badc = 0;
    void add(int clr) {
        sz++;
        int ncnt = ++cnt[clr];
        badc += -(good(clr, ncnt) - good(clr, ncnt-1));
    }
} subt[MN];

subtObj* dfs(int c, int p) {
    subtObj* cnts = &subt[c];
    cnts->add(clr[c]);
    for (auto to : g[c]) {
        if (to != p) {
            auto chCnts = dfs(to, c);

            // small-large merge
            if (chCnts->sz > cnts->sz) swap(chCnts, cnts);
            for (auto p : chCnts->cnt) {
                while (p.sn--)
                    cnts->add(p.fs);
            }
            chCnts->cnt.clear();
        }
    }

    // add edge if some colour is present on both sides (and if the subtree has a parentl edge)
    if (p != -1 && cnts->badc > 0)
        dsu[rt(p)] = rt(c);
    return cnts;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N); N -= 2;

    map<pii, vector<int>> common;
    for (auto i = 0; i < N; i++) {
        int a, b, c;
        cin >> a >> b >> c >> clr[i];
        auto add = [&] (int x, int y) {
            pii p{x, y}; 
            if (p.fs > p.sn) swap(p.fs, p.sn);
            common[p].pb(i);
        };
        add(a, b); add(b, c); add(a, c);
        tcnt[clr[i]]++;
    }
    for (auto &p : common) {
        if (SZ(p.sn) == 2) {
            g[p.sn[0]].pb(p.sn[1]);
            g[p.sn[1]].pb(p.sn[0]);
        }
    }

    // dsu and dfs
    iota(dsu, dsu + N + 1, 0);
    dfs(0, -1);

    // get ans
    unordered_set<int> us;
    for (auto i = 0; i < N; i++)
        us.insert(rt(i));
    cout << (SZ(us) - 1) << '\n';

    return 0;
}