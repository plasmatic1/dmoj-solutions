// coci-08-contest-6-5-dostava.yml
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

const int MR = 2001, MC = 201, MQ = 200001;
int R, C, Q,
    val[MR][MC], psum[MR][MC];

short mk(short a, short b) { return a | (b << 11); }
short ga(short a) { return a & 2047; }
short gb(short a) { return a >> 11; }

using state = ll;
int dis[MR][2][MR][2];
deque<short> q;
bool inq[MR][2];

int suf(int r, int x) { return psum[r][C - 1] - (x ? psum[r][x - 1] : 0); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (R) >> (C);
    for (auto i = 0; i < R; i++) {
        for (auto j = 0; j < C; j++) {
            cin >> (val[i][j]);
            psum[i][j] = val[i][j];
            if (j > 0) psum[i][j] += psum[i][j - 1];
        }
    }

    // SPFA with Small-Label-First Optimization
    // https://en.wikipedia.org/wiki/Shortest_Path_Faster_Algorithm#Optimization_techniques
    memset(dis, 0x3f, sizeof dis);
    for (auto i = 0; i < R; i++) {
        for (auto j = 0; j < 2; j++) {
            auto cdis = dis[i][j];
            q.pb(mk(i, j)); cdis[i][j] = 0; inq[i][j] = true;
            while (!q.empty()) {
                short state = q.front(); q.pop_front();
                int a = ga(state), b = gb(state), y = b * (C - 1), d = cdis[a][b];
                inq[a][b] = false;

                int alt = -1, xx = -1, yy = -1;
#define PUSH(altv, ni, nj) alt = altv, xx = ni, yy = nj; \
                if (alt < cdis[xx][yy]) { \
                    cdis[xx][yy] = alt; \
                    if (!inq[xx][yy]) { \
                        inq[xx][yy] = true; \
                        if (SZ(q) > 1 && d < cdis[ga(q.front())][gb(q.front())]) { \
                            short o = q.front(); q.pop_front(); \
                            q.push_front(mk(xx, yy)); \
                            q.pb(o); \
                        } \
                        else \
                            q.pb(mk(xx, yy)); \
                    } \
                }

                if (a < R - 1) {
                    PUSH(d + val[a + 1][y], a + 1, b); }
                if (a > 0) {
                    PUSH(d + val[a - 1][y], a - 1, b); }
                PUSH(d + psum[a][C - 1] - val[a][y], a, !b);
            }
        }
    }

    // Compute ans
    ll ans = val[0][0];
    int px = 0, py = 0;

    cin >> (Q);
    while (Q--) {
        int x, y;
        cin >> x >> y;
        x--; y--;

        ll mn = LLINF;
        if (x == px) {
            int l = min(y, py), r = max(y, py);
            mina(mn, (ll)psum[x][r] - (l ? psum[x][l - 1] : 0) - val[px][py]);
        }
        for (auto i = 0; i < 2; i++) {
            for (auto j = 0; j < 2; j++) {
                ll cans = dis[px][i][x][j] +
                    (i ? suf(px, py) : psum[px][py]) +
                    ((j ? suf(x, y) : psum[x][y]) - val[x][j * (C - 1)]) -
                    val[px][py];
                mina(mn, cans);
            }
        }
        ans += mn;

        px = x;
        py = y;
    }

    cout << (ans) << '\n';

    return 0;
}