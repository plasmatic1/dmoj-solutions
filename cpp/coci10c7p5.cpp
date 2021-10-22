// ./coci-10-contest-7-5-kuglice.yml
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

struct DSU {
    vector<int> dsu;
    void init(int N) {
        dsu.resize(N + 1);
        iota(dsu.begin(), dsu.end(), 0);
    }
    int rt(int x) { return dsu[x] == x ? x : dsu[x] = rt(dsu[x]); }
    void merge(int x, int y) { // x -> y
        dsu[rt(x)] = rt(y); }
    bool con(int x, int y) { return rt(x) == rt(y); }
};

const int MN = 3e5 + 1;
int N, Q,
    P[MN], ans[MN];
pii qs[MN];
bool gone[MN], cyc[MN];
DSU dsu;

void add(int i) {
    if (!P[i]) return;
    if (dsu.con(i, P[i]))
        cyc[dsu.rt(P[i])] = true;
    else
        dsu.merge(i, P[i]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (auto i = 1; i <= N; i++)
        cin >> P[i];

    dsu.init(N);

    cin >> Q;
    for (auto i = 0; i < Q; i++) {
        int t, x; cin >> t >> x;
        qs[i] = {t, x};
        if (t == 2)
            gone[x] = true;
    }
    for (auto i = 1; i <= N; i++)
        if (!gone[i])
            add(i);

    for (auto i = Q-1; i >= 0; i--) {
        auto [t, x] = qs[i];

        if (t == 2) {
            add(x);
        }
        else {
            int t = dsu.rt(x);
            if (cyc[t]) ans[i] = -1;
            else ans[i] = t;
        }
    }
    for (auto i = 0; i < Q; i++) {
        auto [t, x] = qs[i];
        if (t == 1) {
            cout << (ans[i] == -1 ? "CIKLUS" : to_string(ans[i])) << '\n';
        }
    }

    return 0;
}