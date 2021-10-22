// ./problem-3-replay-double-ignition.yml
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

int M, Q;
vector<int> ps;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> M >> Q;

    ps.pb(1);
    ps.pb(1);
    string tot = "11";
    while (SZ(ps) <= 2 || (ps[SZ(ps)-1] != 1 || ps[SZ(ps)-2] != 1)) {
        ps.pb((ps[SZ(ps)-2] + ps[SZ(ps)-1]) % M);
        tot += to_string(ps.back());
    }
    // cout << "ps=["; for (auto __x:ps)cout<<__x<<", "; cout<<"], "; cout << endl; // db I:ps
    // cout<<"tot="<<(tot)<<", "; cout << endl; // db tot
    // pisano period
    ps.pop_back(); ps.pop_back();
    tot.pop_back(); tot.pop_back();

    while (Q--) {
        ll n; cin >> n;
        n--;
        n %= SZ(tot);
        cout << (tot[n]) << '\n';
    }

    return 0;
}