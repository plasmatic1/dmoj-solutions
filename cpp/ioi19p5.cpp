// ioi-19-p5-vision-program.yml
#include "vision.h"
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

#ifdef LOCAL
int add_not(int N);
int add_and(std::vector<int> Ns);
int add_or(std::vector<int> Ns);
int add_xor(std::vector<int> Ns);
#endif

const int MN = 201, D = 200, MX = MN * 3;
int H, W, K;
map<pii, int> actCoord;

int mk(int r, int c) { return r * W + c; }
void rot(int &x, int &y) {
    int nx = x + y, ny = x - y;
    x = nx; y = ny;
}

int curIns,
    preRowId[MX], preColId[MX], sufRowId[MX], sufColId[MX];

void pushIf(vector<int> &to, int x, int y) {
    auto ptr = actCoord.find(mpr(x, y));
    if (ptr != actCoord.end())
        to.pb(ptr->second);
}

void construct_network(int H0, int W0, int K0) {
    H = H0; W = W0; K = K0;
    curIns = H * W;

    // Rotate Grid
    int minX = INF, maxX = -INF, minY = INF, maxY = -INF;
    for (auto i = 0; i < H; i++) {
        for (auto j = 0; j < W; j++) {
            int tx = i, ty = j;
            rot(tx, ty);
            actCoord[mpr(tx, ty)] = mk(i, j);

            mina(minX, tx); mina(minY, ty);
            maxa(maxX, tx); maxa(maxY, ty);
        }
    }

    // Prefix Row XORs
    for (auto i = minX; i <= maxX; i++) {
        vector<int> pts, ptsSuf;
        int revI = maxX - (i - minX);
        for (auto j = minY; j <= maxY; j++) {
            pushIf(pts, i, j);
            pushIf(ptsSuf, revI, j);
        }
        if (i > minX) pts.pb(preRowId[i - 1 + D]);
        if (revI < maxX) ptsSuf.pb(sufRowId[revI + 1 + D]);
        add_or(pts);
        preRowId[i + D] = curIns++;
        add_or(ptsSuf);
        sufRowId[revI + D] = curIns++;
    }

    // Prefix Col XORs
    for (auto i = minY; i <= maxY; i++) {
        vector<int> pts, ptsSuf;
        int revI = maxY - (i - minY);
        for (auto j = minX; j <= maxX; j++) {
            pushIf(pts, j, i);
            pushIf(ptsSuf, j, revI);
        }
        if (i > minY) pts.pb(preColId[i - 1 + D]);
        if (revI < maxY) ptsSuf.pb(sufColId[revI + 1 + D]);
        add_or(pts);
        preColId[i + D] = curIns++;
        add_or(ptsSuf);
        sufColId[revI + D] = curIns++;
    }

    // Build checks for manhattan distance
    vector<int> atK, pastK;
    for (auto i = minX; i <= maxX; i++) {
        int cx = i + D, nx = i + K + D, nx2 = nx + 1;
        if (nx - D <= maxX) {
            add_and({preRowId[cx], sufRowId[nx]});
            atK.pb(curIns++);
        }
        if (nx2 - D <= maxX) {
            add_and({preRowId[cx], sufRowId[nx2]});
            pastK.pb(curIns++);
        }
    }
    for (auto i = minY; i <= maxY; i++) {
        int cx = i + D, nx = i + K + D, nx2 = nx + 1;
        if (nx - D <= maxY) {
            add_and({preColId[cx], sufColId[nx]});
            atK.pb(curIns++);
        }
        if (nx2 - D <= maxY) {
            add_and({preColId[cx], sufColId[nx2]});
            pastK.pb(curIns++);
        }
    }

    // Compute final answer
    add_or(atK);
    if (pastK.empty()) return; // K is the max Manhattan distance possible.  Simply checking if it's possible suffices
    int atKId = curIns++;
    add_or(pastK);
    int pastKId = curIns++;
    add_not(pastKId);
    int pastKInvId = curIns++;
    add_and({atKId, pastKInvId});
}

#ifdef LOCAL
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}
#endif