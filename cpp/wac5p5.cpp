#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt"
// ./wesleys-anger-contest-5-problem-5.yml
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
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const ll MOD = 998244353;
ll madd(ll a, ll b, ll mod = MOD) { return (a + b) % mod; }
ll msub(ll a, ll b, ll mod = MOD) { return (a - b + mod) % mod; }
ll mmul(ll a, ll b, ll mod = MOD) { return (a * b) % mod; }
ll fpow(ll x, ll y, ll mod = MOD) {
    if (!y) return 1LL;
    return mmul(fpow(mmul(x, x, mod), y >> 1, mod), (y & 1) ? x : 1LL, mod);
}
ll mdiv(ll x, ll y, ll mod = MOD) { return mmul(x, fpow(y, mod - 2, mod), mod); }

const int MN = 360+45;
using mat = array<array<int, MN>, MN>;
using vec = array<int, MN>;

int N, K, E;
bool init[MN][MN];

int msz;
void reset(mat &m) {
    for (auto i = 0; i < msz; i++)
        for (auto j = 0; j < msz; j++)
            m[i][j] = 0LL;
}
void reset(vec &v) {
    for (auto i = 0; i < msz; i++)
        v[i] = 0LL;
}
void copyTo(mat &f, mat &t) {
    for (auto i = 0; i < msz; i++)
        for (auto j = 0; j < msz; j++)
            t[i][j] = f[i][j];
}
void copyTo(vec &f, vec &t) {
    for (auto i = 0; i < msz; i++)
        t[i] = f[i];
}
int getk(int enc) {
    return enc % (K + 1);
}
vector<short> good[MN][MN];
void sqr(mat &m) {
    static mat tmp;
    for (auto i = 0; i < msz; i++) {
        int ik = getk(i);
        for (auto j = 0; j < msz; j++) {
            if (getk(j) > ik) continue;
            __int128_t r = 0;
            for (auto k : good[i][j])
                r += (__int128_t)m[i][k] * m[k][j];
            tmp[i][j] = r % MOD;
        }
    }
    copyTo(tmp, m);
}
void mul(mat &m, vec &v) {
    static vec tmp;
    for (auto i = 0; i < msz; i++) {
        __int128_t r = 0;
        for (auto j = 0; j < msz; j++)
            r += (__int128_t)m[i][j] * v[j];
        tmp[i] = r % MOD;
    }
    copyTo(tmp, v);
}

int encode(int n, int k) {
    return n * (K + 1) + k;
}

mat cmat;
vec cres;

ll compute() {
    reset(cres);
    cres[0] = 1;
    for (auto i = 0; i < 30; i++) {
        if (((E - 1) >> i) & 1) {
            mul(cmat, cres);

            // cout<<"[use]: "; cout<<"i="<<(i)<<", "; cout<<"cres=["; for(int i=0; i<(msz); i++)cout<<cres[i]<<", "; cout<<"], ";cout << endl; // db l:use,i,A:msz:cres
        }
        sqr(cmat);
    }
    assert(encode(N - 1, K) < msz);
    return cres[encode(N - 1, K)];
}

void encodeMatrix(int skip1, int skip2) {
    reset(cmat);
    for (auto i = 0; i <= K; i++) {
        for (auto j = 0; j < N; j++) {
            for (auto k = 0; k < N; k++) {
                if (j == skip1 || j == skip2) continue;
                if (k == skip1 || k == skip2) continue;
                int nk = i + (k == 3);
                if (nk <= K)
                    cmat[encode(k, nk)][encode(j, i)] += init[j][k];
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (E) >> (K);

    for (auto i = 0; i < N; i++) {
        string buf;
        cin >> buf;
        for (auto j = 0; j < N; j++)
            init[i][j] = buf[j] == '1';
    }


    // doesn't matter, skip (1, 2), no E1, no E2
    ll ans = 0;
    msz = N*(K+1);
    for (auto i = 0; i < msz; i++) {
        int ik = getk(i);
        for (auto j = 0; j < msz; j++) {
            int jk = getk(j);
            if (ik < jk) continue;
            for (auto k = 0; k < msz; k++) {
                int kk = getk(k);
                if (ik >= kk && kk >= jk)
                    good[i][j].pb(k);
            }
        }
    }

    encodeMatrix(-1, -1);
    ans = compute();
    // cout<<"ans="<<(ans)<<", "; cout << endl; // db ans
    for (int skip = 1; skip <= 2; skip++) {
        encodeMatrix(skip, -1);
        ans = msub(ans, compute());
    }
    encodeMatrix(1, 2);
    ans = madd(ans, compute());

    cout << (ans) << '\n';

    return 0;
}