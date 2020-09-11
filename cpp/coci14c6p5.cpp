// coci-14-contest-6-5-neo.yml
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

ostream& operator<<(ostream& out, const pii o) {
    out << "(first=" << o.first << ", second=" << o.second << ")";
    return out;
}

/*
Idea: if a 2x2 adjacent grid of 2x2 squares is cool, then the 3x3 that it makes is also cool.
This idea can be extended from (N-1)x(N-1) -> NxN for arbitrary N.

This means that we just need to find the largest subrectangle made up completely of 2x2 cool squares.
Then, the problem just reduces to City Game
*/

const int MN = 1001;
int R, C,
    val[MN][MN], gridHeight[MN][MN];
bool grid[MN][MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (R) >> (C);

    // Input and get grid of 2x2 cool squares
    for (auto i = 0; i < R; i++)
        for (auto j = 0; j < C; j++)
            cin >> (val[i][j]);
    for (auto i = 0; i < R-1; i++)
        for (auto j = 0; j < C-1; j++)
            grid[i][j] = val[i][j] + val[i + 1][j + 1] <= val[i][j + 1] + val[i + 1][j];
    for (auto i = 0; i < R-1; i++) {
        for (auto j = 0; j < C-1; j++) {
            if (i > 0) gridHeight[i][j] = gridHeight[i - 1][j];
            gridHeight[i][j] = gridHeight[i][j] * grid[i][j] + grid[i][j];
        }
    }

    // Get ans
    int ans = 0;
    for (auto i = 0; i < R-1; i++) {
        deque<pii> dq; // loc, height
        for (auto j = 0; j < C-1; j++) {
            int lpos = j;
            while (!dq.empty() && dq.back().second > gridHeight[i][j]) { // from dq.bk().first..j-1
                if (dq.back().second)
                    maxa(ans, (j - dq.back().first + 1) * (dq.back().second + 1));
                lpos = dq.back().first;
                dq.pop_back();
            }
            dq.pb({lpos, gridHeight[i][j]});
        }
        while (!dq.empty()) {
            if (dq.back().second)
                maxa(ans, (C - 1 - dq.back().first + 1) * (dq.back().second + 1));
            dq.pop_back();
        }
    }
    cout << (ans) << '\n';

    return 0;
}