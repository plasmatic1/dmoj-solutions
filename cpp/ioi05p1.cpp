// ./ioi-05-p1-garden.yml
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

const int MN = 250 + 5;
int R, C, N, K,
    psum[MN][MN], grid[MN][MN], lhs[MN], rhs[MN], ptr[MN][MN];

// (a, b) -> (c, d)
int query(int a, int b, int c, int d) {
    return psum[c][d] - psum[a - 1][d] - psum[c][b - 1] + psum[a - 1][b - 1];
}

int perim(int a, int b, int c, int d) {
    return 2 * ((c - a + 1) + (d - b + 1));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (R) >> (C) >> (N) >> (K);
    for (auto i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        grid[x][y]++;
    }

    int ans = INF;
    for (auto _ = 0; _ < 2; _++) {
        memset(psum, 0, sizeof psum);
        for (auto i = 1; i <= R; i++)
            for (auto j = 1; j <= C; j++)
                psum[i][j] = grid[i][j] + psum[i - 1][j] + psum[i][j - 1] - psum[i - 1][j - 1];

        memset(lhs, 0x3f, sizeof lhs);
        for (auto i = 1; i <= C; i++)
            for (auto j = i; j <= C; j++)
                ptr[i][j] = R;
        for (auto i = R; i >= 1; i--) {
            for (auto j = 1; j <= C; j++) {
                for (auto k = j; k <= C; k++) {
                    while (query(ptr[j][k], j, i, k) < K && ptr[j][k] > 1) ptr[j][k]--;
                    if (query(ptr[j][k], j, i, k) == K)
                        mina(lhs[i], perim(ptr[j][k], j, i, k));
                }
            }
        }
        for (auto i = 1; i <= R; i++)
            mina(lhs[i], lhs[i - 1]);

        memset(rhs, 0x3f, sizeof rhs);
        for (auto i = 1; i <= C; i++)
            for (auto j = i; j <= C; j++)
                ptr[i][j] = 1;
        for (auto i = 1; i <= R; i++) {
            for (auto j = 1; j <= C; j++) {
                for (auto k = j; k <= C; k++) {
                    while (query(i, j, ptr[j][k], k) < K && ptr[j][k] < R) ptr[j][k]++;
                    if (query(i, j, ptr[j][k], k) == K)
                        mina(rhs[i], perim(i, j, ptr[j][k], k));
                }
            }
        }
        for (auto i = R; i >= 1; i--) {
            mina(rhs[i], rhs[i + 1]);
            mina(ans, lhs[i - 1] + rhs[i]);
        }

        for (auto i = 1; i <= max(R, C); i++)
            for (auto j = 1; j <= i; j++)
                swap(grid[i][j], grid[j][i]);
        swap(R, C);
    }
    
    cout << (ans == INF ? "NO" : to_string(ans)) << '\n';

    return 0;
}