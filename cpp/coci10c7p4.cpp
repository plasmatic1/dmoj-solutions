// ./coci-10-contest-7-4-poštar.yml
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

const int MN = 51, D[3] = {-1, 0, 1};
int N,
    H[MN][MN];
string grid[MN];

bool vis[MN][MN];
int px, py, mn, mx;

void dfs(int r, int c) {
    if (r < 0 || r >= N || c < 0 || c >= N) {
        return;
    }
    if (H[r][c] < mn || H[r][c] > mx) return;
    if (vis[r][c]) return;

    vis[r][c] = true;
    for (auto i = -1; i <= 1; i++)
        for (auto j = -1; j <= 1; j++)
            dfs(r+i, c+j);
}

bool check(int d) {
    bool ok = false;
    for (auto i = 0; i < N; i++) {
        for (auto j = 0; j < N; j++) {
            mn = H[i][j]-d, mx = H[i][j];
            memset(vis, 0, sizeof vis);
            dfs(px, py);
            bool cok = true;
            for (auto k = 0; k < N; k++)
                for (auto l = 0; l < N; l++)
                    if (grid[k][l] == 'K')
                        cok &= vis[k][l];
            ok |= cok;
        }
    }

    return ok;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (auto i = 0; i < N; i++)
        cin >> grid[i];
    for (auto i = 0; i < N; i++)
        for (auto j = 0; j < N; j++) {
            cin >> H[i][j];
            if (grid[i][j] == 'P')
                px = i, py = j;
        }

    int l = 0, r = 1e7, ans = -1;
    while (l <= r) {
        int mid = (l+r) / 2;
        if (check(mid)) {
            ans = mid;
            r = mid-1;
        }
        else
            l = mid+1;
    }

    cout << (ans) << '\n';

    return 0;
}