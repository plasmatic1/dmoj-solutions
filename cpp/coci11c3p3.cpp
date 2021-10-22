// ./coci-11-contest-3-3-pogodak.yml
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

// 0-indexed
const int LOOKUP[6][2] = {
    {4, 2},
    {0, 2},
    {0, 4},
    {0, 1},
    {0, 3},
    {2, 4}
};

int _getonside(int top, int no) {
    return no <= 1 ? LOOKUP[top][no] : 5-LOOKUP[top][no-2];
}
int getonside(int top, int fw, int no) {
    for (auto i = 0; i < 4; i++)
        if (_getonside(top, i) == fw)
            return _getonside(top, (i+no)%4);
    assert(0); return -1;
}

int R, C;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> R >> C;
    C--; // C now becomes "num of moves"

    int top = 0, fw = 4, cc = C/4, cr = C%4;
    ll ans = 14LL * cc * R;
    for (auto i = 0; i < R; i++) {
        if (i & 1) { // back
            for (auto j = 0; j < cr; j++) {
                ans += top+1;
                int nt = getonside(top, fw, 1);
                top = nt;
            }
        }
        else { // forward
            for (auto j = 0; j < cr; j++) {
                ans += top+1;
                int nt = getonside(top, fw, 3);
                top = nt;
            }
        }
        // add last of col
        ans += top+1;

        // next row
        int nt = fw, nf = 5-top;
        top = nt;
        fw = nf;
    }

    cout << (ans) << '\n';

    return 0;
}