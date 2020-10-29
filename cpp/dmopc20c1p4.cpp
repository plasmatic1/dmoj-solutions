// ./dmopc-20-contest-1-p4.yml
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

// moses why
using VecType = ll;
constexpr ll MOD = 1e9 + 7;
constexpr bool USE_MOD = true;

using Vec = vector<VecType>; using Mat = vector<Vec>;
void init(Mat &m, int N) {
    m.resize(N);
    for (int i = 0; i < N; i++) m[i].assign(N, 0);
}
void init(Vec &v, int N) { v.assign(N, 0); }
void init_identity(Mat &m, int N) {
    init(m, N);
    for (int i = 0; i < N; i++) m[i][i] = 1;
}
void mul(Mat &res, const Mat &a, const Mat &b) {
    int N = a.size();
    init(res, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                res[i][j] += a[i][k] * b[k][j]; if (USE_MOD) { res[i][j] %= MOD; } } } }
}
void mul(Vec &res, const Mat &m, const Vec &v) {
    int N = m.size();
    init(res, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            res[i] += m[i][j] * v[j]; if (USE_MOD) { res[i] %= MOD; } } }
}
Mat mul(const Mat &a, const Mat &b) { Mat ret; mul(ret, a, b); return ret; }
Vec mul(const Mat &m, const Vec &v) { Vec ret; mul(ret, m, v); return ret; }
void exp(Mat &res, ll exp) {
    int N = res.size();
    Mat cpow = res; init_identity(res, N);
    for (ll cxp = 0; exp >> cxp; cxp++) {
        if ((exp >> cxp) & 1)
            res = mul(res, cpow);
        cpow = mul(cpow, cpow);
    }
}

ll N, K, C;
int T;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (K) >> (T) >> (C);

    Mat tr; Vec initial;
    init(initial, T + 1);
    init(tr, T + 1);

    initial[T] = C;
    tr[0][T] = K; tr[T][T] = 1;
    for (auto i = 1; i <= T; i++)
        tr[i][i - 1] = 1;
    // cout << "initial=["; for (auto __x:initial)cout<<__x<<", "; cout<<"], "; cout << endl; // db I:initial
    // for (auto &r : tr) {
    //     cout << "r=["; for (auto __x:r)cout<<__x<<", "; cout<<"], "; cout << endl; // db I:r
    // }
    exp(tr, N - 1);
    Vec fv = mul(tr, initial);
    // cout << "fv=["; for (auto __x:fv)cout<<__x<<", "; cout<<"], "; cout << endl; // db I:fv

    ll ans = 0;
    for (auto i = 0; i < T; i++) ans += fv[i];
    ans += 2 * fv[T];
    ans %= MOD;
    cout << (ans) << '\n';

    return 0;
}