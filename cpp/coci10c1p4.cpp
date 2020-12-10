// ./coci-10-contest-1-4-ljutnja.yml
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
int N, M;
ll val[MN];

ll check(ll maxd) {
    ll res = 0, left = M;
    vector<ll> ds;
    for (auto i = 0; i < N; i++) {
        ll req = max(0LL, val[i] - maxd);
        if (left < req) return LLINF;
        left -= req;
        ll add = val[i] - req;
        ds.pb(add);
    }
    sort(all(ds), greater<ll>());
    for (auto x : ds) {
        if (left > 0) {
            left--;
            x--;
        }
        res += x * x;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (M) >> (N);
    for (auto i = 0; i < N; i++)
        cin >> (val[i]);

    int miss = 0;
    for (auto i = 0; i < N; i++)
        miss += val[i];
    miss = miss - M;

    ll l = -1, r = 1e10;
    while (l + 1 < r) {
        ll mid = (l + r) / 2;
        if (check(mid) != LLINF)
            r = mid;
        else
            l = mid;
    }
    // cout<<"r="<<(r)<<", "; cout << endl; // db r
    cout << check(r) << '\n';

    return 0;
}