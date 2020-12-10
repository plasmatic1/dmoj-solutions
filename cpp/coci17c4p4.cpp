// ./coci-17-contest-4-4-vođe.yml
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

const int MN = 5001;
int N, M, K,
    T[MN];
bool dp[MN][MN];
deque<int> idx[2][MN];
// SUCC
int succ(int i) { return (i+1)%N; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M) >> (K);
    if (K > M) K = M; // K>M is a dumb case

    for (auto i = 0; i < N; i++) cin >> T[i];
    for (auto i = 0; i < N; i++) {
        dp[M-1][i] = !T[i];
        idx[dp[M-1][i]][i].pb(M-1);
    }
    for (auto i = M-2; i >= 0; i--) {
        for (auto j = 0; j < N; j++) {
            auto &q = idx[T[j]][succ(j)];
            while (!q.empty() && q.front() > i + K)
                q.pop_front();
            dp[i][j] = T[j] ^ q.empty();
            // cout<<"i="<<(i)<<", "; cout<<"j="<<(j)<<", "; cout<<"dp[i][j]="<<(dp[i][j])<<", "; cout << endl; // db i,j,dp[i][j]
            // cout << "q=["; for (auto __x:q)cout<<__x<<", "; cout<<"], "; cout << endl; // db I:q
        }
        for (auto j = 0; j < N; j++)
            idx[dp[i][j]][j].pb(i);
    }

    for (auto i = 0; i < N; i++) {
        cout << dp[0][i] << ' ';
    }
    cout << '\n';

    return 0;
}