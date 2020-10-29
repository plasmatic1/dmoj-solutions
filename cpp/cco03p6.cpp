// ./cco-03-p6-cheap-gas.yml
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

struct i_love_you_marcus {
    int x, y, f;
};

const int MN = 101, DIR[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
const ld inf = numeric_limits<ld>::infinity();
int R, C, N, cap;
ld dis[MN][MN][MN * 2], cost[MN][MN];
bool inq[MN][MN][MN * 2];

void solve() {
    cin >> (R) >> (C) >> (cap) >> (N);
    mina(cap, R + C - 2);
    for (auto i = 0; i < R; i++) {
        for (auto j = 0; j < C; j++) {
            cost[i][j] = -1;
            for (auto k = 0; k <= cap; k++)
                dis[i][j][k] = inf;
        }
    }
    for (auto i = 0; i < N; i++) {
        int x, y; ld c;
        cin >> x >> y >> c;
        x--; y--;
        if (cost[x][y] == -1) cost[x][y] = c;
        else mina(cost[x][y], c);
    }

    queue<i_love_you_marcus> q;
    dis[0][0][cap] = 0;
    q.push({0, 0, cap}); inq[0][0][cap] = true;
    while (!q.empty()) {
        auto c = q.front(); q.pop();
        inq[c.x][c.y][c.f] = false;
        ld d = dis[c.x][c.y][c.f], alt;

#define TRY_PUSH(a, b, c, w) alt = d + w; \
        if (alt < dis[a][b][c]) { \
            dis[a][b][c] = alt; \
            if (!inq[a][b][c]) { \
                inq[a][b][c] = true; \
                q.push({a, b, c}); \
            } \
        }

        if (c.f > 0) {
            for (auto &dvec : DIR) {
                int a = c.x + dvec[0], b = c.y + dvec[1];
                if (a >= 0 && a < R && b >= 0 && b < R) {
                    TRY_PUSH(a, b, c.f - 1, 0.);
                }
            }
        }
        if (cost[c.x][c.y] != -1 && c.f < cap) {
            TRY_PUSH(c.x, c.y, c.f + 1, cost[c.x][c.y]);
        }
    }

    ld ans = inf;
    for (auto i = 0; i <= cap; i++)
        mina(ans, dis[R - 1][C - 1][i]);
    if (ans == inf)
        cout << ("Stranded on the shoulder") << '\n';
    else
        cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << fixed << setprecision(2);

    int T;
    cin >> T;
    while (T--) {
        // Input
        
        solve();

        // Reset
    }
}