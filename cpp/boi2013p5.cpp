// boi-2013-p5-tracks-in-the-snow.yml
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

const int MN = 4001;
int R, C;
char grid[MN][MN];
bool vis[MN][MN];

int ans = 0;
queue<pii> nxt, nxStart;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (R) >> (C);
    for (auto i = 0; i < R; i++)
        cin >> (grid[i]);

    bool done = false;
    char cur = grid[0][0];
    nxStart.emplace(0, 0);
    do {
        ans++;
        while (!nxStart.empty()) {
            nxt.push(nxStart.front());
            vis[nxStart.front().first][nxStart.front().second] = true;
            cur = grid[nxStart.front().first][nxStart.front().second];
            nxStart.pop();
        }
        while (!nxt.empty()) {
            auto c = nxt.front(); nxt.pop();
            if (grid[c.first][c.second] != cur) {
                // cout<<"[nx]: "; cout<<"ans="<<(ans)<<", "; cout<<"c.first="<<(c.first)<<", "; cout<<"c.second="<<(c.second)<<", "; cout<<"grid[c.first][c.second]="<<(grid[c.first][c.second])<<", "; cout << endl; // db l:nx,ans,c.first,c.second,grid[c.first][c.second]
                nxStart.push(c);
                continue;
            }
            // cout<<"ans="<<(ans)<<", "; cout<<"c.first="<<(c.first)<<", "; cout<<"c.second="<<(c.second)<<", "; cout << endl; // db ans,c.first,c.second
            for (int xd : {-1, 0, 1}) {
                for (int yd : {-1, 0, 1}) {
                    if (xd && yd) continue;
                    int nx = c.first + xd, ny = c.second + yd;
                    if (nx < 0 || nx >= R || ny < 0 || ny >= C || vis[nx][ny] || grid[nx][ny] == '.') continue;
                    nxt.emplace(nx, ny);
                    vis[nx][ny] = true;
                }
            }
        }
        done = nxStart.empty();
    }
    while (!done);

    cout << (ans) << '\n';

    return 0;
}