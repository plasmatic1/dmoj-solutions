// ./p3-mystery-dag.yml
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

const int MN = 301, MM = MN*MN, LG = 9;
int N, M,
    A[MM], B[MM];
bool dn[MM];

#ifdef LOCAL
int _A[MM], _B[MM];

int _tot=0;
vector<int> query(vector<int> s0, vector<int> s1) {
    // asert
    assert(1 <= SZ(s0) && 1 <= SZ(s1));
    _tot += SZ(s0) + SZ(s1);
    assert(_tot <= 3000);
    vector<bool> inc(N+1);
    for (auto x : s0) {
        assert(1 <= x && x <= N);
        assert(!inc[x]);
        inc[x] = true;
    }
    for (auto x : s1) {
        assert(1 <= x && x <= N);
        assert(!inc[x]);
        inc[x] = true;
    }
    // asert
    
    vector<bool> is0(N+1), is1(N+1);
    for (auto x : s0) is0[x] = true;
    for (auto x : s1) is1[x] = true;

    vector<int> res;
    for (auto i = 0; i < M; i++) {
        if (is0[_A[i]] && is1[_B[i]])
            res.pb(i+1);
    }
    return res;
}
#else
void prvec(vector<int> v) {
    for (auto i = 0; i < SZ(v); i++)
        cout << v[i] << " \n"[i == SZ(v)-1];
}
int _tot=0;
vector<int> query(vector<int> s0, vector<int> s1) {
    // asert
    assert(1 <= SZ(s0) && 1 <= SZ(s1));
    _tot += SZ(s0) + SZ(s1);
    assert(_tot <= 3000);
    vector<bool> inc(N+1);
    for (auto x : s0) {
        assert(1 <= x && x <= N);
        assert(!inc[x]);
        inc[x] = true;
    }
    for (auto x : s1) {
        assert(1 <= x && x <= N);
        assert(!inc[x]);
        inc[x] = true;
    }
    // asert

    cout << ('?') << ' ' << (SZ(s0)) << ' ' << (SZ(s1)) << '\n';
    prvec(s0);
    prvec(s1);
    cout.flush();

    int r; cin >> r; 
    if (r == -1) exit(0);
    vector<int> res(r);
    for (auto &x : res) cin >> x;
    return res;
}
#endif

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (auto i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
#ifdef LOCAL
        _A[i] = a;
        _B[i] = b;
#endif

        if (a > b) swap(a, b);
        A[i] = a;
        B[i] = b;
    }

    for (auto i = 0; i < LG; i++) {
        vector<bool> ina(N+1);
        vector<int> s0, s1;
        for (auto j = 1; j <= N; j++) {
            if ((j >> i) & 1) s1.pb(j);
            else {
                s0.pb(j);
                ina[j] = true;
            }
        }
        if (s0.empty() || s1.empty()) continue;

        vector<bool> atob(M);
        for (auto x : query(s0, s1))
            atob[x-1] = true;

        for (auto j = 0; j < M; j++) {
            if (ina[A[j]] != ina[B[j]]) {
                dn[j] = 0;
                dn[j] ^= ina[B[j]];
                dn[j] ^= !atob[j];
            }
        }
    }

    string ans(M, '0');
    for (auto i = 0; i < M; i++)
        if (dn[i]) {
            ans[i] = '1';

#ifdef LOCAL
            swap(_A[i], _B[i]);
#endif
        }

    cout << ('!') << ' ' << (ans) << '\n';
    cout.flush();

#ifdef LOCAL
    for (auto i = 0; i < M; i++) {
        cout<<"_A[i]="<<(_A[i])<<", "; cout<<"_B[i]="<<(_B[i])<<", "; cout << endl; // db _A[i],_B[i]
        assert(_A[i]<_B[i]);
    }
#endif

    return 0;
}