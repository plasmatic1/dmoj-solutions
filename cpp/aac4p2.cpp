// ./p2-lavish-lights.yml
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

const int MN = 2e5 + 10;
int N, Q;
ll L[MN];

ll gcd(ll a, ll b) {
    return b ? gcd(b, a%b) : a;
}

int tmp[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;

    int end = 0;
    L[0] = 1;
    for (auto i = 1; i <= N; i++) {
        int x; cin >> x;
        tmp[i] = x;

        ll nw = ll(L[i-1]) * x / gcd(L[i-1], (ll)x);
        L[i] = nw;
        end++;

        if (nw > 1e9) {
            break;
        }
    }
    for (auto i = end+1; i <= N; i++) {
        int x; cin >> x;
    }

    while (Q--) {
        int t; cin >> t;

        int l = 1, r = end, ans = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            
            if (t % L[mid] == 0) {
                l = mid+1;
            }
            else {
                r = mid-1;
                ans = mid;
            }
        }

        cout << (ans) << '\n';
    }

    return 0;
}