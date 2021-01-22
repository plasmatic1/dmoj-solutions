// ./wc-17-contest-4-s3-guardians-of-the-cash.yml
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

const int MN = 1001;
int N,
    A[MN][MN], R[MN], C[MN];

ll ans = 0;
bool why() {
    memset(R, 0, sizeof R);
    memset(C, 0, sizeof C);
    for (auto i = 0; i < N; i++)
        for (auto j = 0; j < N; j++)
            maxa(R[i], A[i][j]), maxa(C[j], A[i][j]);
    for (auto i = 0; i < N; i++) R[i] = C[i] = min(R[i], C[i]);
    bool bruh = false;
    for (auto i = 0; i < N; i++) {
        for (auto j = 0; j < N; j++) {
            int q = min(R[i], C[j]);
            if (q < A[i][j]) {
                ans += A[i][j] - q;
                A[i][j] = q;
                bruh = true;
            }
        }
    }
    return bruh;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    for (auto i = 0; i < N; i++) {
        for (auto j = 0; j < N; j++) {
            cin >> (A[i][j]);
        }
    }

    while (why());
    cout << (ans) << '\n';

    return 0;
}