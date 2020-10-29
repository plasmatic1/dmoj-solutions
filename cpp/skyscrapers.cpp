// ./skyscrapers.yml
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
int R, C, _L, _R,
    A[MN], B[MN], psum[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (R) >> (C) >> (_L) >> (_R);
    for (auto i = 0; i < R; i++)
        cin >> (A[i]);
    for (auto i = 0; i < C; i++)
        cin >> (B[i]);
    if (*max_element(A, A + R) != *max_element(B, B + C)) {
        cout << ("Impossible") << '\n';
        return 0;
    }

    sort(B, B + C);
    partial_sum(B, B + C, psum);

    int mn = 0, mx = 0;
    for (auto i = 0; i < R; i++) {
        int idx = lower_bound(B, B + C, A[i]) - B;
        if (idx > 0) mx += A[i] * (C - idx) + psum[idx - 1];
        else mx += A[i] * C;
    }

    map<int, int> cnt1, cnt2;
    for (auto i = 0; i < R; i++) cnt1[A[i]]++;
    for (auto i = 0; i < C; i++) cnt2[B[i]]++;
    for (auto &p : cnt2)
        maxa(cnt1[p.fs], p.sn);
    for (auto &p : cnt1) mn += p.fs * p.sn;

    cout << "Minimum: " << mn * _L << ", maximum: " << mx * _R << '\n';

    return 0;
}