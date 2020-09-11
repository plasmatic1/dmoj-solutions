// coci-18-contest-6-4-simfonija.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define pb push_back
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
template <typename C> int SZ(C &v) { return v.size(); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 1e5 + 1;
int N, K;
ll vals[MN], psum[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (K);
    for (auto i = 1; i <= N; i++)
        cin >> (vals[i]);
    for (auto i = 1; i <= N; i++) {
        int x;
        cin >> x;
        vals[i] = x - vals[i];
    }
    sort(vals + 1, vals + N + 1);
    copy(vals, vals + N + 1, psum);
    partial_sum(psum, psum + N + 1, psum);

    ll ans = LLINF;
    int sz = N - K;
    for (auto i = sz; i <= N; i++) {
        int mid = (i + (i - sz + 1)) / 2, lsz = mid - (i - sz), rsz = i - mid;
        ll midv = vals[mid], cans = (lsz * midv - (psum[mid] - psum[i - sz])) + ((psum[i] - psum[mid]) - rsz * midv);
        mina(ans, cans);
    }

    cout << (ans) << '\n';

    return 0;
}