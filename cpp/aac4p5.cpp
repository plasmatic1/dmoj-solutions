// ./p5-neighborly-neighborhoods.yml
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

const int MN = 5e5 + 1;
int N, M, Q, X;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> X >> Q;
    DSU d; d.init(N);
    for (auto i = 0; i < Q; i++) {
        int x, y; cin >> x >> y;
        d.merge(x, y);
    }

    map<int, vector<int>> _cc;
    for (auto i = 1; i <= N; i++)
        _cc[d.rt(i)].pb(i);
    vector<pair<int, vector<int>>> bysz;
    for (auto [_, v] : _cc)
        bysz.eb(SZ(v), v);
    sort(all(bysz), [&] (const auto &a, const auto &b) { return a.fs > b.fs; });

    if (SZ(bysz) < X) {
        cout << (-1) << '\n';
        return 0;
    }

    for (auto [s, v] : bysz) {
        if (DEBUG) { cout<<"s="<<(s)<<", "; cout << "v=["; for (auto __x:v)cout<<__x<<", "; cout<<"], "; cout << endl; } //__RAW_DEBUG_LINE__:db s,I:v
    }

    vector<vector<int>> comps;
    vector<int> fcomp;
    for (auto i = 0; i < SZ(bysz)-X+1; i++) {
        fcomp.insert(fcomp.end(), all(bysz[i].sn));
    }
    comps.pb(fcomp);
    for (auto i = SZ(bysz)-X+1; i < SZ(bysz); i++)
        comps.pb(bysz[i].sn);

    ll mxe = 0, mne = 0;
    for (auto &v : comps) {
        ll n = SZ(v);
        mxe += n*(n-1);
        if (n > 1) mne += n;
    }

    if (M < mne) {
        cout << (-1) << '\n';
        return 0;
    }

    assert(SZ(comps) == X);
    vector<pii> es;

    M -= mne;
    for (auto &v : comps) {
        if (DEBUG) { cout << "v=["; for (auto __x:v)cout<<__x<<", "; cout<<"], "; cout << endl; } //__RAW_DEBUG_LINE__:db I:v
        ll n = SZ(v);

        UNIQUE(v);
        assert(SZ(v) == n);

        if (n > 1) {
            for (auto i = 0; i < n; i++) {
                es.eb(v[i], v[(i+1)%n]);
            }
        }
        for (auto i = 0; i < n; i++) {
            bool bk = false;
            for (auto j = 0; j < n; j++) {
                if (i != j && (i + 1) % n != j) {
                    if (M > 0) {
                        es.eb(v[i], v[j]);
                        M--;
                    }
                    else {
                        bk = true;
                        break;
                    }
                }
            }
            if (bk) break;
        }
    }

    int sz = SZ(comps);
    for (auto i = 0; i < sz; i++) {
        bool bk = false;
        for (auto j = i+1; j < sz; j++) {
            for (auto x : comps[i]) {
                for (auto y : comps[j]) {
                    if (M > 0) {
                        es.eb(x, y);
                        M--;
                    }
                    else {
                        bk = true;
                        break;
                    }
                }
                if (bk) break;
            }
            if (bk) break;
        }
        if (bk) break;
    }

    if (M > 0) {
        cout << (-1) << '\n';
    }
    else {
        for (auto [a, b] : es)
            cout << (a) << ' ' << (b) << '\n';
    }

    return 0;
}