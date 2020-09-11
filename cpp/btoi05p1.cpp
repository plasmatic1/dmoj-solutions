// ./baltic-oi-05-p1-camouflaged-camp.yml
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

const int MN = 1001;
short R, C, H, W, N;
int psum[MN][MN];
struct Char {
    short x, y, xs, ys;
    bool ver, alt;
} cs[MN];

istream& operator>>(istream &in, Char &o) {
    in >> o.x >> o.y >> o.xs >> o.ys >> o.ver >> o.alt;
    return in;
}

int Q(int x1, int y1, int x2, int y2) {
    return psum[x2][y2] - psum[x2][y1 - 1] - psum[x1 - 1][y2] + psum[x1 - 1][y1 - 1];
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (R) >> (C);
    for (auto i = 1; i <= R; i++)
        for (auto j = 1; j <= C; j++)
            cin >> (psum[i][j]), psum[i][j] += psum[i - 1][j] + psum[i][j - 1] - psum[i - 1][j - 1];
    cin >> (H) >> (W) >> (N);
    for (auto i = 0; i < N; i++)
        cin >> (cs[i]);

    int bmiss = INF, ansx = -1, ansy = -1;
    for (auto i = 1; i <= R-H+1; i++) {
        for (auto j = 1; j <= C-W+1; j++) {
            int cnt = 0;
            for (auto k = 0; k < N; k++) {
                auto &c = cs[k];
                int x = i + c.x - 1, y = j + c.y - 1; //, area = sz[k].fs * sz[k].sn;
                int sum1 = Q(x, y, x + c.xs - 1, y + c.ys - 1), sum2 = 0;
                if (c.ver) {
                    sum2 = Q(x + c.xs, y, x + 2 * c.xs - 1, y + c.ys - 1);
                }
                else {
                    sum2 = Q(x, y + c.ys, x + c.xs - 1, y + 2 * c.ys - 1);
                }

                if ((sum1 >= sum2) != c.alt) cnt++;
                if (cnt > bmiss) break;
            }
            if (cnt < bmiss) {
                bmiss = cnt;
                ansx = i;
                ansy = j;
            }
        }
    }

    cout << (ansx) << ' ' << (ansy) << '\n';

    return 0;
}