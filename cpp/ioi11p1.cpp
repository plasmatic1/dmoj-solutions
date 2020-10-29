// ./ioi-11-p1-tropical-garden.yml
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

void answer(int X);

const int MN = 150000 + 5;
int N, M, P, Q,
    disB[2][MN * 2], disF[2][MN * 2];
vector<pii> g[MN];
vector<int> auxg[MN * 2], auxgr[MN * 2];

void dfs(int c, int cdis, int dis[MN * 2], vector<int> g[MN * 2]) {
    if (dis[c] != -1) return;
    dis[c] = cdis;
    for (int to : g[c])
        dfs(to, cdis + 1, dis, g);
}

void count_routes(int n0, int m0, int p0, int R[][2], int q0, int G[]) {
    N = n0; M = m0; P = p0; Q = q0;
    for (auto i = 0; i < M; i++) {
        g[R[i][0]].eb(i, R[i][1]);
        g[R[i][1]].eb(i, R[i][0]);
    }
    for (auto i = 0; i < N; i++)
        sort(all(g[i]));

    // build auxillary graph
    for (auto i = 0; i < N; i++) {
        for (pii p : vector<pii>{{i, 0}, {i + N, 1}}) {
            int v = p.fs; auto ed = g[i][p.sn % SZ(g[i])];
            int to = ed.sn + N * (ed.fs == g[ed.sn][0].fs);
            auxg[v].pb(to);
            auxgr[to].pb(v);
        }
    }

    // compute dist arrays
    memset(disB, -1, sizeof disB);
    memset(disF, -1, sizeof disF);
    for (auto i = 0; i < 2; i++) {
        int v = P + i * N;
        dfs(v, 0, disB[i], auxgr);
        for (int to : auxg[v])
            dfs(to, 1, disF[i], auxg);
    }

    // brute force queries in O(N)
    for (auto i = 0; i < Q; i++) {
        int ans = 0;
        for (auto j = 0; j < N; j++) {
            bool wk = false;
            for (auto k = 0; k < 2; k++) {
                int v = P + k * N;
                if (disB[k][j] != -1 && G[i] >= disB[k][j]) {
                    wk |= G[i] == disB[k][j];
                    if (disF[k][v] != -1)
                        wk |= (G[i] - disB[k][j]) % disF[k][v] == 0;
                }
            }
            ans += wk;
        }
        answer(ans);
    }
}

#ifdef LOCAL
void answer(int X) {
    cout << (X) << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, P;
    cin >> N >> M >> P;
    int R[M][2];
    for (auto i = 0; i < M; i++)
        cin >> (R[i][0]) >> (R[i][1]);
    int Q;
    cin >> Q;
    int G[Q];
    for (auto i = 0; i < Q; i++)
        cin >> (G[i]);
    count_routes(N, M, P, R, Q, G);
    cout << '\n';

    return 0;
}
#endif