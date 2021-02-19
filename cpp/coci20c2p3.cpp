// ./coci-20-contest-2-3-euklid.yml
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

ll spow(ll a, ll b) {
    ll res = 1; 
    while (b--) res *= a;
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        int g, h;
        cin >> g >> h;

        auto attempt = [&] (ll a, ll b) {
            if (a < b) swap(a, b);
            ll left = (g - (a*b) % g) % g;
            if (left >= a) return mpr(-1LL, -1LL);
            b = b * a + left;
            if (g >= b) return mpr(-1LL, -1LL);
            a *= b;
            a += g;
            return mpr(a, b);
        };

        bool done = false;
        for (auto i = h; i < 2*h; i++) {
            auto res = attempt(i, h);
            if (res != mpr(-1LL, -1LL)) {
                cout << (res.fs) << ' ' << (res.sn) << '\n';
                done = true;
                break;
            }
        }
        if (done) continue;

        // start with h^k, h such that h^k >= g
        ll a = h, b = h;
        while (true) {
            auto res = attempt(a, b);
            if (res != mpr(-1LL, -1LL)) {
                cout << (res.fs) << ' ' << (res.sn) << '\n';
                break;
            }
            a *= h;
        }
    }

    return 0;
}