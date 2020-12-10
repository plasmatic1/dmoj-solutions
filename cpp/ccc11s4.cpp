// ./ccc-11-s4-blood-distribution.yml
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

int ans = 0,
    give[8], take[8];

void push(int a, int b) {
    int res = min(give[a], take[b]);
    ans += res;
    give[a] -= res;
    take[b] -= res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (auto i = 0; i < 8; i++)
        cin >> (give[i]);
    for (auto i = 0; i < 8; i++)
        cin >> (take[i]);

    for (auto i = 0; i < 8; i++) push(i, i);
    for (auto i = 0; i < 4; i++) push(2*i, 2*i+1);
    push(3, 7); push(5, 7); // A/B+ to AB+
    push(2, 6); push(4, 6); // A/B- to AB-
    push(2, 7); push(4, 7); // A/B- to AB+
    push(0, 2); push(0, 4); // O- to A/B-
    push(1, 3); push(1, 5); // O- to A/B+
    push(0, 3); push(0, 5); // O- to A/B+
    push(0, 6); push(1, 7); push(0, 7); // O- to AB-, O+ to AB+, O- to AB+

    cout << (ans) << '\n';

    return 0;
}