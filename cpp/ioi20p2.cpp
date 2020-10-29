// supertree.yml
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

struct DSU {
    vector<int> dsu;
    void init(int N) {
        dsu.resize(N + 1);
        iota(dsu.begin(), dsu.end(), 0);
    }
    int rt(int x) { return dsu[x] == x ? x : dsu[x] = rt(dsu[x]); }
    void merge(int x, int y) { // x -> y
        dsu[rt(x)] = rt(y); }
    bool same(int x, int y) { return rt(x) == rt(y); }
};

void build(vector<vector<int>> v);

int construct(vector<vector<int>> g) {
    int N = SZ(g);
    vector<vector<int>> ansg(N, vector<int>(N));

    DSU d; d.init(N);
    for (auto i = 0; i < N; i++) {
        for (auto j = 0; j < N; j++) {
            if (g[i][j])
                d.merge(i, j);
            // symmetrical
            if (g[i][j] != g[j][i]) return 0;
            // impossible if 3
            if (g[i][j] == 3) return 0;
        }
    }
    vector<vector<int>> comp(N);
    for (auto i = 0; i < N; i++)
        comp[d.rt(i)].pb(i);

    auto _A = [&] (int x, int y) -> void {
        ansg[x][y] = ansg[y][x] = true;
    };

    // with components
    for (auto i = 0; i < N; i++) {
        if (!comp[i].empty()) {
            auto &cc = comp[i];
            // cout<<"i="<<(i)<<", "; cout << "cc=["; for (auto __x:cc)cout<<__x<<", "; cout<<"], "; cout << endl; // db i,I:cc
            if (SZ(cc) == 1) continue;
            for (auto x : cc) 
                for (auto y : cc) 
                    if (!g[x][y] || !g[y][x])
                        return 0;

            DSU dd; dd.init(N);
            for (auto x : cc)
                for (auto y : cc)
                    if (g[x][y] == 1)
                        dd.merge(x, y);
            vector<vector<int>> ccomp(N);
            vector<int> roots;
            for (auto x : cc) {
                ccomp[dd.rt(x)].pb(x);
                roots.pb(dd.rt(x));
            }
            UNIQUE(roots);

            // check
            for (auto x : cc)
                for (auto y : cc)
                    if ((g[x][y] == 1) != dd.same(x, y))
                        return 0;

            // build graph
            if (SZ(roots) >= 2) {
                if (SZ(roots) == 2) return 0;
                for (auto i = 0; i < SZ(roots); i++)
                    _A(roots[i], roots[(i + 1) % SZ(roots)]);
            }
            for (auto x : cc) {
                if (!ccomp[x].empty()) {
                    for (auto j = 0; j < SZ(ccomp[x])-1; j++)
                        _A(ccomp[x][j], ccomp[x][j + 1]);
                }
            }
        }
    }

    build(ansg);
    return 1;
}

#ifdef LOCAL
int N;
vector<vector<int>> req, ans;
void build(vector<vector<int>> v) { ans = v; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    req.assign(N, vector<int>(N));
    for (auto i = 0; i < N; i++)
        for (auto j = 0; j < N; j++)
            cin >> (req[i][j]);
    int correct;
    cin >> correct;

    int out = construct(req);
    cout<<"out="<<(out)<<", "; cout<<"correct="<<(correct)<<", "; cout << endl; // db out,correct
    if (out) {
        cout << "Graph:" << endl;
        for (auto i = 0; i < N; i++)
            for (auto j = i; j < N; j++)
                if (ans[i][j])
                    cout << (i) << ' ' << (j) << '\n';
    }

    return 0;
}
#endif