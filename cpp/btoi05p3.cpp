// ./baltic-oi-05-p3-maze.yml
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
    int x, y; bool c;
};
ostream& operator<<(ostream& out, const Ed o) {
    out << "(x=" << o.x << ", y=" << o.y << ", c=" << o.c << ")";
    return out;
}

const int MN = 501;
int R, C, sx, sy, ex, ey,
    dis[MN][MN][2];
vector<Ed> g[MN][MN];

void add(int a, int b, int c, int d, char c_) {
    if (c_ == 'n') return;
    bool cc = c_ == 'w';
    g[a][b].pb({c, d, cc});
    g[c][d].pb({a, b, cc});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (C) >> (R) >> (sy) >> (sx) >> (ey) >> (ex);
    R++; C++;

    for (auto i = 0; i < R-1; i++) {
        string s;
        cin >> s;
        for (auto j = 0; j < C-1; j++)
            add(i, j, i, j + 1, s[j]);

        cin >> s;
        for (auto j = 0; j < C; j++)
            add(i, j, i + 1, j, s[2 * j]);
        for (auto j = 1; j < C; j++)
            add(i, j, i + 1, j - 1, s[2 * j - 1]);
    }
    string s;
    cin >> s;
    for (auto i = 0; i < C-1; i++)
        add(R-1, i, R-1, i + 1, s[i]);

    memset(dis, -1, sizeof dis);
    queue<Ed> q;
    for (auto i = 0; i < 2; i++) {
        dis[sx][sy][i] = 0;
        q.push({sx, sy, (bool)i});
    }
    while (!q.empty()) {
        auto c = q.front(); q.pop();
        int ndis = dis[c.x][c.y][c.c] + 1;
        // cout<<"c="<<(c)<<", "; cout<<"ndis-1="<<(ndis-1)<<", "; cout << endl; // db c,ndis-1
        for (auto to : g[c.x][c.y]) {
            if (to.c == c.c) continue;
            if (dis[to.x][to.y][to.c] == -1) {
                dis[to.x][to.y][to.c] = ndis;
                q.push(to);
            }
        }
    }

    int ans = INF;
    for (auto i = 0; i < 2; i++)
        if (dis[ex][ey][i] != -1)
            mina(ans, dis[ex][ey][i]);
    cout << (ans) << '\n';

    return 0;
}