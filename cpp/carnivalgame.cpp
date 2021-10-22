// ./carnival-game.yml
#include <bits/stdc++.h>
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
#if __cplusplus == 201703L // CPP17 only things
template <typename T> using opt_ref = optional<reference_wrapper<T>>; // for some templates
#endif
using ll = long long; using ull = unsigned long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<long long, long long>;
#ifdef __GNUG__
// PBDS order statistic tree
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T, class comp = less<T>> using os_tree = tree<T, null_type, comp, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename V, class comp = less<K>> using treemap = tree<K, V, comp, rb_tree_tag, tree_order_statistics_node_update>;
// HashSet
#include <ext/pb_ds/assoc_container.hpp>
template <typename T, class Hash> using hashset = gp_hash_table<T, null_type, Hash>;
template <typename K, typename V, class Hash> using hashmap = gp_hash_table<K, V, Hash>;
const ll RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { ll operator()(ll x) const { return x ^ RANDOM; } };
#endif
// More utilities
int SZ(string &v) { return v.length(); }
template <typename C> int SZ(C &v) { return v.size(); }
template <typename C> void UNIQUE(vector<C> &v) { sort(v.begin(), v.end()); v.resize(unique(v.begin(), v.end()) - v.begin()); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 2e3+1;
int N,
    T[MN], dis[MN][MN], sw[MN][MN];
string g[MN];
pii par[MN][MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> N;
    for (auto i = 0; i < N-1; i++)
        cin >> g[i];
    for (auto i = 0; i < N; i++)
        cin >> T[i];

    memset(dis, INF, sizeof dis);
    dis[0][0] = 0;
    deque<pii> q;
    q.eb(0, 0);
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop_front();
        if (x == N-1) continue;
        int cd = dis[x][y];

        auto push = [&] (int a, int b, int w, int px, int py) {
            if (0 <= a && a < N && 0 <= b && b <= a) {
                if (cd+w < dis[a][b]) {
                    dis[a][b] = cd+w;
                    par[a][b] = {px, py};
                    sw[a][b] = w;
                    if (w) q.eb(a, b);
                    else q.emplace_front(a, b);
                }
            }
        };

        push(x+1, y, g[x][y] == 'R', x, y);
        push(x+1, y+1, g[x][y] == 'L', x, y);
    }

    int ans = INT_MIN, best = -1;
    for (auto i = 0; i < N; i++) {
        int alt = T[i] - dis[N-1][i];
        if (alt > ans) {
            ans = alt;
            best = i;
        }
    }

    cout << (ans) << '\n';

    int x = N-1, y = best;
    vector<pii> need;
    while (x > 0) {
        auto [px, py] = par[x][y];
        if (sw[x][y])
            need.eb(px+1, py+1);

        x = px;
        y = py;
    }

    cout << (SZ(need)) << '\n';
    for (auto [x, y] : need)
        cout << (x) << ' ' << (y) << '\n';

    return 0;
}