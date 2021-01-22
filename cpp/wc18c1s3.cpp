// ./wc-18-contest-1-s3-reach-for-the-top.yml
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

const int MN = 1e6 + 1;
int H, N, J,
    dp[MN];
bool block[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (H) >> (J) >> (N);
    for (auto i = 0; i < N; i++) {
        int l, r;
        cin >> l >> r;
        for (auto j = l; j <= r; j++)
            block[j] = true;
    }

    memset(dp, 0x3f, sizeof dp);
    dp[0] = 0;
    priority_queue<pii> pq;
    int ans = INF;
    for (auto i = 0; i <= H; i++) {
        if (!block[i]) {
            if (J <= i && !block[i-J])
                dp[i] = min(dp[i], dp[i-J] + 1);
            // cout<<"i="<<(i)<<", "; cout<<"dp[i]="<<(dp[i])<<", "; cout << endl; // db i,dp[i]
            if (i + J >= H)
                mina(ans, dp[i] + 1);
            while (!pq.empty() && pq.top().fs > dp[i] + 1) {
                auto c = pq.top(); pq.pop();
                dp[c.sn] = dp[i] + 1;
                c.fs = dp[i] + 1;
                pq.push(c);
            }
            pq.emplace(dp[i], i);
        }
    }

    cout << (ans == INF ? -1 : ans) << '\n';

    return 0;
}