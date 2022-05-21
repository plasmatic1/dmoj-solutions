// ./p2-secret-sequence.yml
#include <bits/stdc++.h>
#define DEBUG 1
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

// M = ceil(N/2) for... reasons

int query(int l, int r) {
    cout << "? " << l << ' ' << r << '\n';
    cout.flush();
    int res; cin >> res; assert(res != -1);
    return res;
}

const int MN = 1e5 + 1;
int N;
int ans[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    // guess left
    int all = query(1, N), txor = 0, h = N / 2;
    for (auto i = 0; i < h; i++) {
        int q = query(i+2, N) ^ txor ^ all;
        ans[i] = q;
        txor ^= q;
    }
    // guess right
    txor = 0;
    for (auto i = N-1; i > h; i--) {
        int q = query(1, i) ^ all ^ txor;
        ans[i] = q;
        txor ^= q;
    }
    // guess middle
    txor = 0;
    for (auto i = 0; i < N; i++)
        txor ^= ans[i]; // ans[h]=0 initially so it doesn't matter
    ans[h] = all ^ txor;

    cout << "! ";
    for (auto i = 0; i < N; i++)
        cout << ans[i] << " \n"[i == N-1];
    cout.flush();

    return 0;
}