// ./wesleys-anger-contest-6-problem-4-canadian-christmas-cactus.yml
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

// I came up with this problem while sitting on the toilet one day
// And I solved it 2 months later after thinking about it for a very long time

void cute(int a, int b, int c, int d) {
    map<int, int> fre;
    fre[a]++; fre[b]++; fre[c]++; fre[d]++;
    vector<int> q;
    for (auto p : fre)
        if (p.sn == 1)
            q.pb(p.fs);
    cout << (q[0]) << ' ' << (q[1]) << '\n';
}

const int MN = 2e5 + 1;
int N;
vector<int> g[MN];

bool aqt(int c, int p) {
    vector<int> eric;
    for (auto to : g[c]) {
        if (to != p) {
            bool dormi = aqt(to, c);
            if (!dormi)
                eric.pb(to);
            if (SZ(eric) == 2) {
                cute(c, eric[0], c, eric[1]);
                eric.clear();
            }
        }
    }
    if (SZ(eric) == 1 && p != -1) {
        cute(p, c, c, eric[0]);
        return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    for (auto i = 0; i < N-1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }
    cout << ((N-1)/2) << '\n';
    aqt(1, -1);

    return 0;
}