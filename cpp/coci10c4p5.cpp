// ./coci-10-contest-4-5-dugovi.yml
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

const int MN = 2e5 + 1;
int N,
    to[MN], D[MN], mon[MN], indeg[MN];

int vis[MN], tov[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (auto i = 0; i < N; i++) {
        cin >> to[i] >> D[i];
        to[i]--;
        indeg[to[i]]++;
    }

    int ans = 0;
    queue<int> q;
    for (auto i = 0; i < N; i++)
        if (indeg[i] == 0)
            q.push(i);
    while (!q.empty()) {
        auto c = q.front(); q.pop();
        if (mon[c] < D[c]) {
            ans += D[c]-mon[c];
            mon[c] = D[c];
        }

        mon[to[c]] += D[c];
        if (--indeg[to[c]] == 0)
            q.push(to[c]);
    }

    for (auto i = 0; i < N; i++) {
        if (!vis[i]) {
            vector<int> chk;
            int c = i;
            for (; vis[c] == 0; c = to[c]) {
                vis[c] = 1;
                chk.pb(c);
            }
            if (vis[c] == 1) { // cycle
                int st = c, minv = INF, tot = 0; 
                for (int c = st; ;) {
                    tov[to[c]] = D[c];

                    c = to[c];
                    if (c == st) break;
                }
                for (int c = st; ;) {
                    tot += max(0, D[c]-mon[c]-tov[c]);
                    mina(minv, max(0, D[c]-mon[c]));

                    c = to[c];
                    if (c == st) break;
                }
                ans += tot + minv;
            }
            for (auto x : chk) vis[x] = 2;
        }
    }

    cout << (ans) << '\n';

    return 0;
}