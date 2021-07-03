// ./dmopc-20-contest-6-p2-interpretive-art.yml
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

const int MN = 5e5 + 1;
int N,
    A[MN], B[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    vector<int> a1, b1;
    for (auto i = 0; i < N; i++) {
        cin >> A[i];
        if (A[i]) a1.pb(i);
    }
    for (auto i = 0; i < N; i++) {
        cin >> B[i];
        if (B[i]) b1.pb(i);
    }
    if (SZ(a1) != SZ(b1))
        return cout << "-1\n", 0;

    vector<pii> ops;
    for (auto i = N-1; i >= 0; ) {
        if (B[i] == 0) {
            i--;
            continue;
        }

        int j = i;
        while (j >= 0 && B[j] == 1) j--;
        // j+1..i = 1s

        int lst = 0;
        bool none = true;
        for (auto k = i; k > j; k--) {
            lst = a1.back();
            none &= a1.back() == k;
            if (a1.back() > k)
                return cout << "-1\n", 0;

            a1.pop_back();
        }
        if (!none)
            ops.eb(lst, i);

        i = j;
    }

    cout << (SZ(ops)) << '\n';
    for (auto [l, r] : ops)
        cout << (l+1) << ' ' << (r+1) << '\n';

    return 0;
}