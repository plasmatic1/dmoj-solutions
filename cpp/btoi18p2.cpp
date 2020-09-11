// ./baltic-oi-18-p2-martian-dna.yml
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
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 2e5 + 1;
int N, K, R,
    req[MN], val[MN];

int goodc = 0,
    cnt[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (K) >> (R);
    for (auto i = 1; i <= N; i++)
        cin >> (val[i]);
    for (auto i = 0; i < R; i++) {
        int t, a;
        cin >> t >> a;
        req[t] = a;
    }

    int r = 0, ans = INF;
    for (int l = 1; l <= N; l++) {
        while (r < N && goodc < R) {
            r++;
            int pre = cnt[val[r]]++, t = val[r];
            if (pre < req[t] && cnt[t] >= req[t]) goodc++;
        }
        // cout<<"l="<<(l)<<", "; cout<<"r="<<(r)<<", "; cout<<"goodc="<<(goodc)<<", "; cout << endl; // db l,r,goodc
        if (goodc == R)
            mina(ans, r - l + 1);

        int pre = cnt[val[l]]--, t = val[l];
        if (pre >= req[t] && cnt[t] < req[t]) goodc--;
    }

    cout << (ans == INF ? "impossible" : to_string(ans)) << '\n';

    return 0;
}