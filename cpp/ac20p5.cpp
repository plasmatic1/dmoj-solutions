// ./appleby-contest-20-p5-ridiculous-tree.yml
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

/*
 * DP recurrence for node (n):
 *
 * for each child, compute the number of possible permutations in its subtree.  Then, we can 'merge' the permutations in as many ways possible.
 *
 * This is equivalent to doing product(dp[child] for all children) * (number of ways to permute the SIZE(n)-1 nodes)
 *
 * This second value is simply equal to the number of permutations of K values where there are c_0 values that are 0, c_1 values that are 1, etc... AKA: K!/c_0!c_1!c_2!...
 */

const int MN = 4e5 + 1;
int N,
    sz[MN];
vector<int> g[MN];

int dfs(int c) {
    sz[c] = 1;
    for (auto to : g[c])
        sz[c] += dfs(to);
    return sz[c];
}

// sieve
int jmp[MN];
vector<int> pf[MN];

// difference array
int ssum[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    assert(1 <= N && N <= 400000);
    for (auto i = 2; i <= N; i++) {
        int p;
        cin >> p;
        g[p].pb(i);
    }
    // for (int i = 1; i <= N; i++) assert(g[i].size() <= 20);
    // get subtree sizes
    dfs(1);

    // do sieve and compute prime factorization of numbers 1..N
    iota(jmp, jmp + N + 1, 0);
    for (auto i = 2; i <= N; i++) {
        if (jmp[i] == i) {
            for (int j = i * 2; j <= N; j += i)
                jmp[j] = i;
        }
    }
    for (auto i = 2; i <= N; i++) {
        for (int c = i; c > 1; c /= jmp[c])
            pf[i].pb(jmp[c]);
    }

    // compute answer in terms of a bunch of factorials
    for (auto i = 1; i <= N; i++) {
        ssum[sz[i] - 1]++;
        for (auto to : g[i])
            ssum[sz[to]]--;
    }
    for (auto i = N-1; i >= 1; i--)
        ssum[i] += ssum[i+1];

    // compute answer
    map<int, ll> ans;
    for (auto i = 1; i <= N; i++)
        for (auto f : pf[i])
            ans[f] += ssum[i];
    // remove entries that are "0"
    vector<int> rem;
    for (auto p : ans)
        if (!p.sn)
            rem.pb(p.fs);
    for (auto x : rem)
        ans.erase(ans.find(x));
    // print
    cout << (SZ(ans)) << '\n';
    for (auto p : ans)
        cout << (p.fs) << ' ' << (p.sn) << '\n';

    return 0;
}