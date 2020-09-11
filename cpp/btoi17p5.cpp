// ./baltic-oi-17-p5-plus-minus.yml
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

const ll MOD = 1e9 + 7;
ll madd(ll a, ll b, ll mod = MOD) { return (a + b) % mod; }
ll msub(ll a, ll b, ll mod = MOD) { return (a - b + mod) % mod; }
ll mmul(ll a, ll b, ll mod = MOD) { return (a * b) % mod; }
ll fpow(ll x, ll y, ll mod = MOD) {
    if (!y) return 1LL;
    return mmul(fpow(mmul(x, x, mod), y >> 1, mod), (y & 1) ? x : 1LL, mod);
}
ll mdiv(ll x, ll y, ll mod = MOD) { return mmul(x, fpow(y, mod - 2, mod), mod); }

#define map unordered_map

const int MK = 2e5 + 1;
int N, M, K;
set<int> use, useType[2];
// vector<int> g[MK];
map<int, vector<pii>> g;
map<int, int> force, oldForce;

ll compute(int i, int forceType) {
    int init, end, inc;
    ll cans;
    if (forceType < 2) {
        init = forceType * N + 1, end = N + forceType * M, inc = forceType * N;
        cans = fpow(2, (forceType ? N : M) - 1 - SZ(useType[!forceType]));
    }
    else {
        init = end = inc = -1;
        cans = 1;
    }
    // cout<<"i="<<(i)<<", "; cout<<"forceType="<<(forceType)<<", "; cout<<"init="<<(init)<<", "; cout<<"end="<<(end)<<", "; cout<<"cans="<<(cans)<<", "; cout << endl; // db i,forceType,init,end,cans

    map<int, int> clr;
    bool bad = false;
    function<void(int, int)> dfs = [&] (int c, int cclr) {
        bool isvis = clr.count(c);
        if (isvis || force.count(c)) {
            int adjClr = isvis ? clr[c] : force[c];
            if (adjClr != cclr) {
                bad = true;
                return;
            }
            if (isvis) return;
        }
        clr[c] = cclr;
        // cout<<"i="<<(i)<<", "; cout<<"c="<<(c)<<", "; cout<<"cclr="<<(cclr)<<", "; cout<<"cans="<<(cans)<<", "; cout << endl; // db i,c,cclr,cans
        for (auto to : g[c]) {
            dfs(to.fs, cclr ^ i ^ to.sn);
            if (bad) return;
        }
    };

    if (forceType < 2) {
        for (auto x : useType[forceType]) {
            int nd = x + inc;
            bool nv = ((nd - init) & 1) ^ i;
            auto ptr = force.find(nd);
            if (ptr != force.end() && ptr->sn != nv) {
                bad = true;
                break;
            }
            force[nd] = nv;
        }
    }
    else {
        for (auto j = 0; j < 2; j++) {
            for (auto x : useType[j]) {
                int nd = x + (N * j), init = (j * N + 1);
                bool nv = ((nd - init) & 1) ^ i;
                auto ptr = force.find(nd);
                if (ptr != force.end() && ptr->sn != nv) {
                    bad = true;
                    break;
                }
                force[nd] = nv;
            }
        }
    }

    for (auto p : force) {
        if (bad) break;
        if (!clr.count(p.fs)) {
            dfs(p.fs, p.sn);
            if (bad) break;
        }
    }
    for (auto j : use) {
        if (bad) break;
        if (!clr.count(j)) {
            dfs(i, 0);
            if (bad) break;
            cans = mmul(cans, 2);
        }
    }
    cans *= !bad;
    // cout<<"cans="<<(cans)<<", "; cout << endl; // db cans

    force = oldForce;
    return cans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M) >> (K);
    int forceOrigin = -1;
    for (auto i = 0; i < K; i++) {
        char t; int x, y;
        cin >> t >> x >> y;
        bool tt = t == '+';

        if (x > 1) { use.insert(x); useType[0].insert(x); }
        if (y > 1) { use.insert(N + y); useType[1].insert(y); }

        if (x == 1 && y == 1)
            forceOrigin = tt;
        else if (y == 1)
            force[x] = tt;
        else if (x == 1)
            force[N + y] = tt;
        else {
            int a = x, b = N + y;
            g[a].eb(b, tt);
            g[b].eb(a, tt);
        }
    }

    // cout << "useType[0]=["; for (auto x:useType[0])cout<<x<<", "; cout<<"], "; cout << "useType[1]=["; for (auto x:useType[1])cout<<x<<", "; cout<<"], "; cout << endl; // db I:useType[0],I:useType[1]

    oldForce = force;
    ll ans = 0;
    for (auto i = 0; i < 2; i++) {
        if (forceOrigin != -1 && i != forceOrigin) continue;
        for (int forceType = 0; forceType < 2; forceType++)
            ans = madd(ans, compute(i, forceType));
        ans = msub(ans, compute(i, 2));
    }
    cout << (ans) << '\n';

    return 0;
}