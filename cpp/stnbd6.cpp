// ./terminus-est.yml
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

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    if (n == 1)
        return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}
vector<ll> multiply(vector<ll> const& a, vector<ll> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<ll> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}

/*

0, 1, 1
Conv:

0

1
1
0 1
0 1(1)

1 1

-> [1, 4, 2]

*/

const int MN = 1e5 + 1;
int N, Q,
    val[MN];
vector<int> g[MN];

// cent
int sz[MN];
bool block[MN];
ll cnt[MN];

int gsz(int c, int p) {
    sz[c] = 1;
    for (int to : g[c])
        if (to != p && !block[to])
            sz[c] += gsz(to, c);
    return sz[c];
}
int gcent(int c, int p, int lim) {
    for (int to : g[c])
        if (to != p && !block[to] && sz[to] > lim) 
            return gcent(to, c, lim);
    return c;
}
void ensure(vector<ll> &v, int sz) {
    while (SZ(v) < sz) v.pb(0);
}
void apply(vector<ll> &v, ll mul, int sh) {
    // auto w = vector<ll>(all(v)); w[0]++;
    auto conv = multiply(v, v);
    for (auto i = 0; i < SZ(v); i++) {
        conv[i * 2] -= v[i];
        if (mul == 1)
            conv[i] += 2 * v[i];
    }
    // cout << "conv=["; for (auto x:conv)cout<<x<<", "; cout<<"], "; cout << endl; // db I:conv
    for (auto i = 0; i < SZ(conv); i++) {
        cnt[i + sh] += (conv[i] * mul) / 2;
    }
}
void dfs(int c, int p, int dis, vector<ll> &ccnt) {
    ensure(ccnt, dis + 1);
    ccnt[dis]++;
    for (int to : g[c])
        if (to != p && !block[to])
            dfs(to, c, dis + val[to], ccnt);
}
void decomp(int c) {
    gsz(c, -1);
    // cnt[val[c]]++; // extra path not accounted for
    if (sz[c] == 1) return;
    int cent = gcent(c, -1, sz[c] / 2);

    vector<ll> tcnt;
    for (int to : g[cent]) {
        if (!block[to]) {
            vector<ll> ccnt;
            dfs(to, cent, val[to], ccnt);

            apply(ccnt, -1, val[cent]);
            // cout<<"c="<<(c)<<", "; cout<<"cent="<<(cent)<<", "; cout<<"to="<<(to)<<", "; cout << "ccnt=["; for (auto x:ccnt)cout<<x<<", "; cout<<"], "; cout << endl; // db c,cent,to,I:ccnt
            // for (auto &x : conv) x /= 2, assert(x%2==0);
            ensure(tcnt, SZ(ccnt));
            for (auto i = 0; i < SZ(ccnt); i++)
                tcnt[i] += ccnt[i];
        }
    }
    // for (auto &x : conv) x /= 2, assert(x%2==0);
    // cout<<"c="<<(c)<<", "; cout<<"cent="<<(cent)<<", "; cout << "tcnt=["; for (auto x:tcnt)cout<<x<<", "; cout<<"], "; cout << endl; // db c,cent,I:tcnt
    apply(tcnt, 1, val[cent]);

    block[cent] = true;
    for (int to : g[cent])
        if (!block[to])
            decomp(to);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    for (auto i = 1; i <= N; i++)
        cin >> (val[i]);
    for (auto i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b); g[b].pb(a);
    }

    decomp(1);
    // cout<<"cnt=["; for(int i=0; i<(N+1); i++)cout<<cnt[i]<<", "; cout<<"], ";cout << endl; // db A:N+1:cnt
    partial_sum(cnt, cnt + N + 1, cnt);

    cin >> (Q);
    while (Q--) {
        int a, b;
        cin >> a >> b;

        ll ans = cnt[b];
        if (a > 0) ans -= cnt[a - 1];
        cout << (ans) << '\n';
    }

    return 0;
}