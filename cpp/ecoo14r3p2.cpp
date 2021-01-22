// ./ecoo-14-r3-p2-mothers-and-daughters.yml
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

const int MN = 2001;
int N, M, 
    p[MN];
vector<int> g[MN];
unordered_map<string, int> mp;

int nou(int c, int left) {
    if (!left) return 1;
    int res = 0;
    if (left > 0) {
        for (auto to : g[c])
            res += nou(to, left-1);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (M);
    for (auto i = 0; i < M; i++) {
        string a, b;
        cin >> a >> b;
        int A, B;
        A = mp.count(a) ? mp[a] : mp[a] = ++N;
        B = mp.count(b) ? mp[b] : mp[b] = ++N;
        g[A].pb(B);
        p[B] = A;
    }
    for (auto i = 0; i < 10; i++) {
        string s;
        cin >> s;
        int X = mp[s];
        int sis = nou(p[X], 1) - 1, cus = nou(p[p[X]], 2) - sis - 1;
        cout << "Cousins: " << cus << ", Sisters: " << sis << '\n';
    }

    return 0;
}