// ./fox-socks.yml
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

template <typename T> void read_fhc_array(vector<T> &v, int k, int inc = 1, ll dval = -1) {
    for (auto i = 0; i < k; i++)
        cin >> v[i];
    ll a, b, c, d;
    cin >> a >> b >> c;
    if (dval == -1) cin >> d;
    else d = dval;
    for (auto i = k; i < (int)v.size(); i++)
        v[i] = (a * v[i - 2] + b * v[i - 1] + c) % d + inc;
}

const ll MOD = 1e9;
const int MN = 1e6 + 1;
int N, Q;

ll asum(ll x) { return x * (x + 1) / 2; }

struct Node {
    // cumulative
    ll sum, sumMod[2];
    int szs[2];

    // lazy flags
    ll lazySet, lazyInc, lazyArInc;
    bool isLazySet;

    void push(int l, int r) {
        lazySet %= MOD;
        lazyInc %= MOD;
        lazyArInc %= MOD;

        ll sz = r - l + 1;
        if (isLazySet) {
            sum = sz * lazySet;
            for (auto i = 0; i < 2; i++)
                sumMod[i] = szs[i] * (lazySet & 1);
        }
        if (lazyInc) {
            sum += sz * lazyInc;
            if (lazyInc & 1)
                for (auto i = 0; i < 2; i++)
                    sumMod[i] = szs[i] - sumMod[i];
        }
        if (lazyArInc) {
            sum += lazyArInc * ((asum(r) - asum(l - 1)) % MOD);
            if (lazyArInc & 1)
                sumMod[1] = szs[1] - sumMod[1];
        }

        sum %= MOD;
    }

    void pushInto(Node &c) {
        if (isLazySet) {
            c.isLazySet = true;
            c.lazySet = lazySet;
            c.lazyInc = c.lazyArInc = 0;
        }
        if (lazyInc) c.lazyInc += lazyInc;
        if (lazyArInc) c.lazyArInc += lazyArInc;
    }

    void clearLazy() {
        lazySet = lazyInc = lazyArInc = isLazySet = 0;
    }
};
Node seg[MN * 2];
#define MID int mid = (l + r) / 2, lhs = i + 1, rhs = i + (mid - l + 1) * 2;

void push(int i, int l, int r) {
    MID;
    auto &s = seg[i];
    s.push(l, r);
    if (l != r) {
        s.pushInto(seg[lhs]);
        s.pushInto(seg[rhs]);
    }
    s.clearLazy();
}

void build(vector<ll>::iterator A, int i = 1, int l = 1, int r = N) {
    auto &s = seg[i];
    s.clearLazy();
    if (l == r) {
        s.sumMod[0] = s.sumMod[1] = s.szs[0] = s.szs[1] = 0;
        s.sum = A[l - 1];
        s.sumMod[l & 1] = s.sum & 1;
        s.szs[l & 1] = 1; 
        return;
    }
    MID;
    build(A, lhs, l, mid); build(A, rhs, mid + 1, r);

    s.sum = seg[lhs].sum + seg[rhs].sum;
    for (auto j = 0; j < 2; j++) {
        s.szs[j] = seg[lhs].szs[j] + seg[rhs].szs[j];
        s.sumMod[j] = seg[lhs].sumMod[j] + seg[rhs].sumMod[j];
    }

    s.sum %= MOD;
}

struct UpdObj {
    bool t; // t=0->query type 1, t=1->query type 2
    ll c, d;
} uo;

void update(int ql, int qr, int i = 1, int l = 1, int r = N) {
    push(i, l, r);
    if (ql > r || qr < l) return;
    auto &s = seg[i];
    if (l >= ql && r <= qr) {
        if (uo.t == 0) {
            s.lazyInc = uo.c;
            s.lazyArInc = uo.d;
        }
        else {
            s.isLazySet = true;
            s.lazySet = uo.c;
        }
        push(i, l, r);
        return;
    }
    MID;
    update(ql, qr, lhs, l, mid); update(ql, qr, rhs, mid + 1, r);

    s.sum = seg[lhs].sum + seg[rhs].sum;
    for (auto j = 0; j < 2; j++)
        s.sumMod[j] = seg[lhs].sumMod[j] + seg[rhs].sumMod[j];

    s.sum %= MOD;
}

// qt=0->normal sum, qt=1->#(odd) sum
ll query(int ql, int qr, bool qt, int i = 1, int l = 1, int r = N) {
    if (ql > r || qr < l) return 0LL;
    push(i, l, r);
    auto &s = seg[i];
    if (l >= ql && r <= qr) return qt ? s.sumMod[0] + s.sumMod[1] : s.sum;
    MID;
    return query(ql, qr, qt, lhs, l, mid) + query(ql, qr, qt, rhs, mid + 1, r);
}

void solve() {
    cin >> (N) >> (Q);
    vector<ll> S(N), O(Q), A(Q), B(Q), C(Q), D(Q);
    read_fhc_array(S, 2, 0, MOD);
    read_fhc_array(O, 2, 1, 4);
    read_fhc_array(A, 2, 1, N);
    read_fhc_array(B, 2, 1, N);
    read_fhc_array(C, 2, 0, MOD);
    read_fhc_array(D, 2, 0, MOD);

    build(S.begin());
    ll tot = 0;
    for (auto i = 0; i < Q; i++) {
        ll ans = 0;
        int r1 = min((ll)N, A[i] + B[i] - 1), r2 = A[i] + B[i] - N - 1;
        if (O[i] == 1) {
            // num added
            ans = C[i] * B[i] + D[i] * ((B[i] * (B[i] - 1) / 2) % MOD);

            // add new socks
            uo = {0, (C[i] - A[i] * D[i]) % MOD, D[i]};
            update(A[i], r1);
            if (r2 >= 1) {
                /*
                 * 1 2 3 4 5*1 2 3 4 5
                 *      +1+2+3+4
                 *
                 * A=4, B=4
                 */
                uo = {0, (C[i] + (N - A[i]) * D[i]) % MOD, D[i]};
                update(1, r2);
            }
        }
        else if (O[i] == 2) {
            // num added
            ans = C[i] * B[i];

            // find num removed and add new socks
            uo = {1, C[i], -1};
            ans += query(A[i], r1, 0);
            update(A[i], r1);
            if (r2 >= 1) {
                ans += query(1, r2, 0);
                update(1, r2);
            }
        }
        else if (O[i] == 3) {
            // Note: qt=0 since we're counting sum
            ans += query(A[i], r1, 0);
            if (r2 >= 1)
                ans += query(1, r2, 0);
        }
        else {
            // Note: qt=1 since we're counting #(odd)
            ans += query(A[i], r1, 1);
            if (r2 >= 1)
                ans += query(1, r2, 1);
        }

        tot = (tot + ans % MOD) % MOD;
    }

    if (tot < 0) tot += MOD;
    cout << (tot) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for (int caseno = 1; caseno <= T; caseno++) {
        // Input
       
        cout << "Case #" << caseno << ": ";
        solve();

        // Reset
#ifndef LOCAL
        cerr << "Done case #" << caseno << endl;
#endif
    }

    return 0;
}