// ./s5-coin-game.yml
#include <bits/stdc++.h>
#define DEBUG 0
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

const int MN = 401;
int N, K,
    dp1[MN][MN], dp2[MN][MN], psum[MN]; // dp1[left][right], dp2[prefix][number of ops]
string s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> s >> K;
    N = SZ(s);
    s = ' ' + s;

    for (auto i = 1; i <= N; i++)
        psum[i] = psum[i-1] + (s[i] == 'H');

    for (auto len = 1; len <= N; len++) {
        int end = N-len+1;
        for (auto l = 1; l <= end; l++) {
            int r = l+len-1;
            for (auto k = l; k <= r; k++) {
                if (s[k] == 'H') {
                    maxa(dp1[l][r], dp1[l][k-1] + dp1[k+1][r] + len);
                }
            }
        }
    }

    for (auto i = 1; i <= N; i++) {
        for (auto j = 0; j <= K; j++) {
            maxa(dp2[i][j], dp2[i-1][j]);
            for (auto k = 0; k < i; k++) {
                int num_ops = psum[i] - psum[k];
                if (num_ops <= j)
                    maxa(dp2[i][j], dp2[k][j - num_ops] + dp1[k+1][i]);
            }
        }
    }

    cout << (dp2[N][K]) << '\n';

    return 0;
}