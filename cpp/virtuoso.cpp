// ./virtuoso.yml
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

const int MN = 1e5 + 1;
int N;
vector<vector<pii>> cur, pre;

// 0->up, 1->none, 2->down (from previous)
void reset(vector<vector<pii>> &dp, pii v = mpr(INF, INF)) {
    dp.assign(7, vector<pii>(3, v));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    reset(pre);
    int n;
    cin >> n;
    for (auto i = 0; i < n; i++) {
        int x;
        cin >> x;
        x--;
        for (auto j = 0; j < 3; j++)
            pre[x][j] = mpr(0, 0);
    }
    for (auto i = 0; i < N-1; i++) {
        reset(cur);
        int n;
        cin >> n;
        for (auto j = 0; j < n; j++) {
            int x;
            cin >> x;
            x--;
            for (auto k = 0; k < 7; k++) {
                for (auto l = 0; l < 3; l++) {
                    int dir = k == x ? 1 : (k < x ? 0 : 2);
                    auto pp = pre[k][l];
                    mina(cur[x][dir], mpr(pp.fs + abs(k - x), pp.sn + (dir != l)));
                }
            }
        }
        pre.swap(cur);
    }

    pii ans(INF, INF);
    for (auto i = 0; i < 7; i++)
        for (auto j = 0; j < 3; j++)
            mina(ans, pre[i][j]);
    cout << (ans.fs) << ' ' << (ans.sn) << '\n';

    return 0;
}