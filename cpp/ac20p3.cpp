// ./appleby-contest-20-p3-ridiculous-string.yml
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

const int MN = 5e5 + 5;
int N, M, 
    nxt[MN][26];
string s, T;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M) >> (s) >> (T);
    assert(1 <= N && N <= 500000);
    assert(1 <= M && M <= 500000);

    memset(nxt, 0x3f, sizeof nxt);
    for (auto i = 0; i < N; i++) {
        int c = s[i] - 'a';
        if (nxt[N][c] == INF) nxt[N][c] = i;
    }
    for (auto i = N-1; i >= 0; i--) {
        int c = s[i] - 'a';
        for (auto j = 0; j < 26; j++)
            nxt[i][j] = nxt[i+1][j];
        nxt[i][c] = i;
    }

    ll ans = -1;
    for (auto i = 0; i < M; i++) {
        int c = T[i] - 'a', t = nxt[(ans + 1) % N][c], loc = ans % N, delta = t - loc;
        if (t == INF) {
            cout << (-1) << '\n';
            return 0;
        }
        if (delta <= 0) delta += N;
        ans += delta;
    }
    cout << (ans+1) << '\n';

    return 0;
}