// ./coci-20-contest-1-4-papričice.yml
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

const int MN = 2e5 + 1;
int N;
vector<int> g[MN];

int sz[MN];
int dfs(int c, int p) {
    sz[c] = 1;
    for (auto to : g[c])
        if (to != p)
            sz[c] += dfs(to, c);
    return sz[c];
}

struct DS {
    multiset<int> ss;
    void init() {
        ss.clear();
        ss.insert(-INF);
        ss.insert(INF);
    }
    void add(int x) { ss.insert(x); }
    void rem(int x) { ss.erase(ss.find(x)); }
    int get(int x) {
        auto nxt = ss.lower_bound(x), pre = nxt; pre--;
        if (*nxt - x < x - *pre) return *nxt;
        return *pre;
    }
} Main, Par;

int ans = INF;
void dfs2(int c, int p) {
    // get ans
    int C = sz[c], k = N - C, _want = k / 2;
    auto attempt = [&] (int b, int c) {
        if (b < 0 || c < 0) return;
        int A[3] = {b, c, N - b - c};
        sort(A, A + 3);
        ans = min(ans, A[2] - A[0]);
    };
    for (int want = _want - 2; want <= _want + 2; want++) {
        attempt(Main.get(want), C);
        attempt(Par.get(want + sz[c]) - sz[c], C);
    }

    // go to children

    // initially c is a parent
    Par.add(sz[c]);
    for (auto to : g[c])
        if (to != p)
            dfs2(to, c);

    // now it becomes a child
    Par.rem(sz[c]);
    Main.add(sz[c]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    for (auto i = 0; i < N-1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }

    dfs(1, -1);

    // get ans
    Main.init(); Par.init();
    dfs2(1, -1);
    for (auto i = 1; i <= N; i++)
        reverse(all(g[i]));
    Main.init(); Par.init();
    dfs2(1, -1);

    cout << (ans) << '\n';

    return 0;
}