// ./p3-that-pool.yml
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

const int MN = 101;
int R, C, Q;
string grid[MN];
vector<pii> blood, head;

void collect() {
    blood.clear();
    head.clear();
    for (auto i = 0; i < R; i++) {
        for (auto j = 0; j < C; j++) {
            if (grid[i][j] == 'X')
                head.eb(i, j);
            else if (grid[i][j] == 'W')
                blood.eb(i, j);
        }
    }
}

void rebuild() {
    for (auto i = 0; i < R; i++)
        grid[i] = string(C, '.');
    for (auto [x, y] : blood) grid[x][y] = 'W';
    for (auto [x, y] : head) grid[x][y] = 'X';
}

bool inbound(int r, int c) { return 0 <= r && r < R && 0 <= c && c < C; }

void prune(vector<pii> &v) {
    vector<pii> fix;
    for (auto &[x, y] : v) {
        if (inbound(x, y))
            fix.eb(x, y);
    }
    v = fix;
}

bool moveBlood() {
    bool did = false;
    for (auto i = 0; i < R; i++) {
        auto doRow = [&] () {
            bool cdid = false;
            for (auto j = 0; j < C; j++) {
                if (grid[i][j] == 'W') {
                    if (inbound(i, j-1) && grid[i][j-1] == '.') {
                        swap(grid[i][j], grid[i][j-1]);
                        cdid = true;
                    }
                }
            }
            return cdid;
        };
        while (doRow()) {
            did = true;
        }
    }

    collect();
    vector<pii> pos;
    for (auto i = 0; i < R; i++) {
        for (auto j = 0; j < C; j++) {
            if (grid[i][j] == 'W') {
                if (inbound(i+1, j) && grid[i+1][j] == '.') {
                    pos.eb(i, j);
                    did = true;
                }
            }
        }
    }
    for (auto [x, y] : pos) swap(grid[x][y], grid[x+1][y]);

    return did;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> R >> C;
    for (auto i = 0; i < R; i++)
        cin >> grid[i];
    cin >> Q;

    while (Q--) {
        int t; cin >> t;

        if (t == 1) {
            collect();
            for (auto &[x, y] : head) x++;
            prune(head);
            rebuild();
            // for (auto i = 0; i < R; i++)
            //     cout << (grid[i]) << '\n';
            while (moveBlood());
        }
        else {
            for (auto i = 0; i < R; i++)
                cout << (grid[i]) << '\n';
        }
    }

    return 0;
}