// ./p3-snowy-slopes.yml
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

void reduce(int &n, int &d) {
    int g = __gcd(n, d);
    n /= g;
    d /= g;
    if (d < 0) {
        n *= -1;
        d *= -1;
    }
}

void reduce(ll &n, ll &d) {
    ll g = __gcd(n, d);
    n /= g;
    d /= g;
    if (d < 0) {
        n *= -1;
        d *= -1;
    }
}

const int MN = 1e5+1;
int N, M;
vector<pii> pts;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;

    for (auto i = 0; i < N; i++) {
        int x, y; cin >> x >> y;
        pts.eb(x, y);
    }

    vector<pii> slopes;
    for (auto i = 0; i < M; i++) {
        int rise, run; cin >> rise >> run;
        reduce(rise, run);
        slopes.eb(rise, run);
    }
    UNIQUE(slopes);

    ll ans = 0;
    for (auto [p, q] : slopes) {
        map<ll, int> fre;
        for (auto [x, y] : pts) {
            fre[(ll)y * q - (ll)x * p]++;
        }

        for (auto [_, v] : fre)
            ans += ll(v)*(v-1)/2;
    }

    cout << (ans) << '\n';

    return 0;
}