// ./path-finder-2-electric-boogaloo.yml
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

struct seg {
    int i, l, r;
    bool operator<(const seg &o) const {
        return r == o.r ? l < o.l : r < o.r;
    }
};
ostream& operator<<(ostream& out, const seg o) {
    out << "(i=" << o.i << ", l=" << o.l << ", r=" << o.r << ")";
    return out;
}

const int MN = 5e5 + 1;
int N, M, Q, K,
    node = 0;
vector<int> ind[MN];
vector<seg> ss[MN];

// dsu
int dsu[MN*2];
void init() { iota(dsu, dsu + node + 1, 0); }
int rt(int x) { return dsu[x] == x ? x : dsu[x] = rt(dsu[x]); }
void unite(int x, int y) { dsu[rt(x)] = rt(y); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M) >> (K) >> (Q);
    for (auto i = 1; i <= N; i++) {
        ind[i].pb(0);
        ind[i].pb(M+1);
    }
    for (auto i = 0; i < K; i++) {
        int r, c;
        cin >> r >> c;
        ind[r].pb(c);
    }
    for (auto i = 1; i <= N; i++) {
        sort(all(ind[i]));
        for (int j = 0; j < SZ(ind[i]) - 1; j++) {
            int l = ind[i][j]+1, r = ind[i][j+1]-1;
            if (l <= r)
                ss[i].pb({++node, l, r});
        }
    }
    init();
    for (auto i = 1; i < N; i++) {
        auto &cur = ss[i], &nxt = ss[i+1];
        int sz = SZ(nxt), ptr = 0;
        for (auto &s : cur) {
            if (ptr > 0) ptr--;
            while (ptr < sz && nxt[ptr].r < s.l) ptr++;
            while (ptr < sz && nxt[ptr].l <= s.r) {
                unite(s.i, nxt[ptr].i);
                ptr++;
            }
        }
    }
    while (Q--) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        auto s1 = *lower_bound(all(ss[r1]), seg{-1, -1, c1});
        auto s2 = *lower_bound(all(ss[r2]), seg{-1, -1, c2});
        cout << (rt(s1.i) == rt(s2.i) ? "YES" : "NO") << '\n';
    }

    return 0;
}