// back-to-school-18-the-golden-porcupine.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define pb push_back
#define mpr make_pair
#define mtp make_tuple
#define all(x) (x).begin(), (x).end()
// Basic type definitions
using ll = long long; using ull = unsigned long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<long, long>;
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
template <typename C> int sz(C &v) { return v.size(); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

/*

:wink: :wink: :smirk: :smirk:
04/07/2020 owo

a(x-L)^2 + b(x-L) + c
= a(x^2 + L^2 - 2xL) + bx - bL + c
= ax^2 - 2aLx + bx + (c - bL + aL^2)
= ax^2 + (b - 2aL)x + (c - bL + aL^2)

*/

const int MT = 1e5 + 10;
int N, T;
ll dif[3][MT];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (T);
    for (auto i = 0; i < N; i++) {
        ll l, r, a, b, c;
        cin >> l >> r >> a >> b >> c;

        ll ta = a, tb = b - 2 * a * l, tc = c - b * l + a * l * l;
        dif[2][l] += ta; dif[2][r + 1] -= ta;
        dif[1][l] += tb; dif[1][r + 1] -= tb;
        dif[0][l] += tc; dif[0][r + 1] -= tc;
    }
    for (auto i = 0; i < 3; i++)
        partial_sum(dif[i], dif[i] + T + 1, dif[i]);

    for (auto i = 1; i <= T; i++) {
        ll cx = 1, ans = 0;
        for (auto j = 0; j < 3; j++) {
            ans += cx * dif[j][i];
            cx *= i;
        }
        cout << ans << ' ';
    }

    return 0;
}