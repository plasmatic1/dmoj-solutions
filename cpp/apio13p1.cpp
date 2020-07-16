// apio-13-p1-robots.yml
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

int mk(int a, int b) {
    return (a << 10) | b;
}
int fst(int p) { return p >> 10; }
int snd(int p) { return p & 1023; }

const int MN = 501, DIR[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int DEF_PII = mk(INF, INF), DEF_INVALID = mk(-1, -1);
int N, W, H;
char grid[MN][MN];

// computing the ending position of moving in different directions from a starting position
int toPos[MN][MN][4];
bool instk[MN][MN];
stack<int> stk;
int compute(int x, int y, int dir) {
    auto &res = toPos[x][y][dir];
    if (res != DEF_PII) return res;
    if (grid[x][y] == 'x') return res = mk(-1, -1);

    stk.push(mk(x, y));
    instk[x][y] = true;

    int nx = x + DIR[dir][0], ny = y + DIR[dir][1];
    if (nx >= 0 && nx < H && ny >= 0 && ny < W) {
        if (instk[nx][ny]) res = mk(-1, -1);
        else if (grid[nx][ny] == 'x') res = mk(x, y);
        else if (grid[nx][ny] == 'A') res = compute(nx, ny, (dir + 3) % 4);
        else if (grid[nx][ny] == 'C') res = compute(nx, ny, (dir + 1) % 4);
        else res = compute(nx, ny, dir);
    }
    else res = mk(x, y);

    stk.pop();
    instk[x][y] = false;

    return res;
}

// DP-related stuffs
int spos[10];
int dp[10][10][MN][MN];

// BFS
queue<int> q;
vector<pii> ins;

// mode=0->init bfs (a is startnum), mode=1->bfs from level (a..b, b+1..c is level)
void bfs(int dis[MN][MN], int mode, int a, int b, int c) {
    if (mode == 0) {
        ins.emplace_back(0, spos[a]); }
    else {
        for (auto i = 0; i < H; i++) {
            for (auto j = 0; j < W; j++) {
                int alt = dp[a][b][i][j] + dp[b + 1][c][i][j];
                if (alt < dis[i][j])
                    ins.emplace_back(alt, mk(i, j));
            }
        }
    }
    sort(all(ins), greater<pii>());

#define D dis
#define PUSH_POS auto &ipos = ins.back().second; \
        if (D[fst(ipos)][snd(ipos)] > ins.back().first) { \
            D[fst(ipos)][snd(ipos)] = ins.back().first; \
            q.push(ipos); \
        } \
        ins.pop_back();

    while (!ins.empty()) {
        PUSH_POS;

        while (!q.empty()) {
            auto c = q.front(); q.pop();
            int cdis = D[fst(c)][snd(c)];
            while (!ins.empty() && ins.back().first < cdis + 1) {
                PUSH_POS;
            }
            for (auto to : toPos[fst(c)][snd(c)]) {
                if (to == DEF_INVALID) continue;
                if (D[fst(to)][snd(to)] > cdis + 1) {
                    D[fst(to)][snd(to)] = cdis + 1;
                    q.push(to);
                }
            }
        }
    }

#undef D
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (W) >> (H);
    for (auto i = 0; i < H; i++) {
        cin >> (grid[i]);
        for (auto j = 0; j < W; j++) {
            if ('1' <= grid[i][j] && grid[i][j] <= '9') {
                spos[grid[i][j] - '0'] = mk(i, j); }
        }
    }

    // compute toPos
    for (auto i = 0; i < H; i++)
        for (auto j = 0; j < W; j++)
            for (auto k = 0; k < 4; k++)
                toPos[i][j][k] = mk(INF, INF);
    for (auto i = 0; i < H; i++)
        for (auto j = 0; j < W; j++)
            for (auto k = 0; k < 4; k++)
                compute(i, j, k);

    // do DP
    memset(dp, 0x3f, sizeof dp);
    for (int len = 1; len <= N; len++) {
        int end = N - len + 1;
        for (auto l = 1; l <= end; l++) {
            int r = l + len - 1;
            if (l == r) {
                bfs(dp[l][r], 0, l, -1, -1); }
            else {
                for (auto k = l; k < r; k++) {
                    bfs(dp[l][r], 1, l, k, r); }
            }
        }
    }

    // get ans
    int ans = INF;
    for (auto i = 0; i < H; i++)
        for (auto j = 0; j < W; j++)
            mina(ans, dp[1][N][i][j]);
    cout << ((ans == INF ? -1 : ans)) << '\n';

    return 0;
}