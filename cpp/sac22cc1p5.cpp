// ./p5-that-wall.yml
#include <bits/stdc++.h>
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

// template is 1-indexed
template <typename T> struct Ranks {
    vector<T> ranks;
    void init() {
        sort(ranks.begin(), ranks.end());
        ranks.resize(unique(ranks.begin(), ranks.end()) - ranks.begin());
    }
    template <typename It> void init(It st, It en) { ranks = vector<T>(st, en); init(); }
    void add(T v) { ranks.push_back(v); }
    int get(T v) { return lower_bound(ranks.begin(), ranks.end(), v) - ranks.begin() + 1; }
    int rget(int k) { return ranks[k-1]; }
    int size() { return ranks.size(); }
};

const int MN = 150 + 5;
int N, K;
ll C[MN], H[MN], dp[MN][MN][MN];
Ranks<int> rs;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> N >> K;
    for (auto i = 1; i <= N; i++) cin >> C[i];
    for (auto i = 1; i <= N; i++) {
        cin >> H[i];
        rs.add(H[i]);
    }
    rs.add(0);
    rs.init();

    memset(dp, 0x3f, sizeof dp);
    dp[0][0][rs.get(0)] = 0; // id ops height
    for (auto i = 0; i < N; i++) {
        for (auto j = 0; j <= K; j++) {
            for (auto k = 1; k <= SZ(rs); k++) {
                // no do
                mina(dp[i+1][j][k], dp[i][j][k] + C[i+1] * abs(rs.rget(k) - H[i+1]));
                // do
                if (j < K) {
                    for (auto l = 1; l <= SZ(rs); l++)
                        mina(dp[i+1][j+1][l], dp[i][j][k] + C[i+1] * abs(rs.rget(l) - H[i+1]));
                }
            }
        }
    }

    ll ans = LLINF;
    for (auto i = 0; i <= K; i++)
        for (auto j = 1; j <= SZ(rs); j++)
            mina(ans, dp[N][i][j]);
    cout << (ans) << '\n';

    return 0;
}