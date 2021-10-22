// ./canada-day-contest-2021-fine-art.yml
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

using T = tuple<int, int, int>;

const int MN = 150001, MV = 101, D[3] = {-1, 0, 1};
int N, Q,
    id[MV][MV][MV];
queue<T> q;

bool okdim(int k) { return 0 <= k && k <= 100; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;

    memset(id, -1, sizeof id);
    for (auto i = 0; i < N; i++) {
        int x, y, z; cin >> x >> y >> z;
        id[x][y][z] = i;
        q.emplace(x, y, z);
    }
    while (!q.empty()) {
        auto [x, y, z] = q.front(); q.pop();
        for (auto xd : D) {
            for (auto yd : D) {
                for (auto zd : D) {
                    int ox = x+xd, oy = y+yd, oz = z+zd, mdis = abs(x-ox)+abs(y-oy)+abs(z-oz);
                    if (mdis != 1) continue;
                    if (okdim(ox) && okdim(oy) && okdim(oz) && id[ox][oy][oz] == -1) {
                        id[ox][oy][oz] = id[x][y][z];
                        q.emplace(ox, oy, oz);
                    }
                }
            }
        }
    }

    while (Q--) {
        int x, y, z; cin >> x >> y >> z;
        cout << (id[x][y][z]+1) << '\n';
    }

    return 0;
}