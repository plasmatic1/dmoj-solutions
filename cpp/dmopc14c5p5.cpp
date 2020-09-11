// ./dmopc-14-contest-6-p5-attack-on-anti-spiral.yml
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

struct Ed {
    int v; ll w;
    bool operator<(const Ed &o) const {
        return w > o.w;
    }
};

const int MN = 1e5 + 1, MNODE = MN * 2;
int N, M;
vector<Ed> g[MN];

// dijk
ll dis[MN];
priority_queue<Ed> pq;

// tarjan
vector<int> auxg[MNODE];
int cord = 0, nodeCtr,
    ord[MN], low[MN], compNo[MN], ecnt[MNODE];
ll esum[MNODE], auxDis[MNODE];
vector<pair<pii, ll>> stk;

void dfs(int c, int p) {
    ord[c] = low[c] = ++cord;
    for (auto to : g[c]) {
        if (to.v != p) {
            if (!ord[to.v]) {
                stk.eb(mpr(c, to.v), to.w);
                dfs(to.v, c);
                mina(low[c], low[to.v]);
                if (low[to.v] >= ord[c]) {
                    int compNo = ++nodeCtr, u, v;
                    do {
                        u = stk.back().fs.fs; v = stk.back().fs.sn;
                        ll w = stk.back().sn;
                        stk.pop_back();

                        ecnt[compNo]++;
                        esum[compNo] += w;
                        auxg[compNo].pb(v);
                        auxg[v].pb(compNo);
                    } while (u != c || v != to.v);
                    auxg[compNo].pb(c);
                    auxg[c].pb(compNo);
                }
            }
            else if (ord[to.v] < ord[c]) {
                stk.eb(mpr(c, to.v), to.w);
                mina(low[c], ord[to.v]);
            }
        }
    }
}

void dfsAux(int c, int p) {
    if (ecnt[c] == 1) return void(auxDis[c] = -1);
    for (int to : auxg[c]) {
        if (to != p) {
            auxDis[to] = auxDis[c] + esum[to];
            dfsAux(to, c);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M);
    for (auto i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].pb({b, c});
        g[b].pb({a, c});
    }

    // BCC
    nodeCtr = N;
    dfs(1, -1);
    // Dijk
    memset(dis, 0x3f, sizeof dis);
    dis[1] = 0; pq.push({1, 0LL});
    while (!pq.empty()) {
        auto c = pq.top(); pq.pop();
        if (c.w > dis[c.v]) continue;
        for (auto to : g[c.v]) {
            ll alt = c.w + to.w;
            if (alt < dis[to.v]) {
                dis[to.v] = alt;
                pq.push({to.v, alt});
            }
        }
    }
    // Dfs Aux
    memset(auxDis, -1, sizeof auxDis);
    auxDis[1] = 0; dfsAux(1, -1);

    for (auto i = 2; i <= N; i++) {
        if (auxDis[i] == -1)
            cout << (1) << ' ' << (dis[i]) << '\n';
        else 
            cout << (2) << ' ' << (auxDis[i]) << '\n';
    }

    return 0;
}