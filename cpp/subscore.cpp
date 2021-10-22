// ./substring-scoring.yml
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

/*
 * Assume `s` is a string that is 0-indexed
 * Let pi[i] -> longest proper prefix `k` of s[0..i] s.t. s[0..k-1] == s[i-k+1..i].  This is known as prefix property
 *
 * 1: pi[i-1] -> pi[i] can increase by at most 1.  If this was not the case, then we can delete the last character of
 * pi[i] and obtain a better result for pi[i-1]
 *
 * 2: To calculate pi[i] we enumerate all values `j` s.t. the prefix property holds for s[0..i-1], and pick the longest one
 * s.t. s[j] == s[i].  This follows from (1)
 *
 * 2a: We can do this by repeatedly picking the largest value of `j` we have not tried yet
 * 2b: To do this we can begin with pi[i-1] (which is by definition the largest `j`) and move iteratively from there
 * 2c: pi[i-1] allows us to map s[i-pi[i-1]+1..i] to s[0..pi[i-1]-1], which means that the next largest `j` will be at
 * pi[pi[i-1]-1] (which is the first pi[i-1] chars of s and is guaranteed to be less than pi[i-1].  We then repeat
 * iteratively until we find a value.
 */
template <typename Container> vector<int> kmp(int N, const Container &s) {
    vector<int> pi(N);
    for (int i = 1; i < N; i++) {
        int cur = pi[i-1];
        while (cur && s[i] != s[cur]) cur = pi[cur-1];
        if (s[i] == s[cur]) cur++;
        pi[i] = cur;
    }
    return pi;
}

struct Comp {
    using Data = int;
    const Data vdef = 0;
    void applyUpdate(Data &to, Data &v) { maxa(to, v); }
    int transformInd(int idx, int N) { return N-idx+1; }
};
template <typename Comp> struct BIT {
    using Data = typename Comp::Data; Comp C;
    int N; vector<Data> bit;
    void init(int n0) {
        N = n0;
        bit.assign(N + 1, C.vdef);
    }
    void update(int x, Data v) {
        x = C.transformInd(x, N);
        for (; x <= N; x += x & -x)
            C.applyUpdate(bit[x], v);
    }
    Data query(int x) {
        x = C.transformInd(x, N);
        Data res = C.vdef;
        for (; x; x -= x & -x)
            C.applyUpdate(res, bit[x]);
        return res;
    }
};

const int MN = 1e5 + 1;
int mx[MN];
string p, s, t;
BIT<Comp> bit;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> p >> s >> t;

    string tmp1 = s + '$' + p, tmp2 = t + '$' + s; reverse(all(tmp1));
    auto pi1 = kmp(SZ(tmp1), tmp1), pi2 = kmp(SZ(tmp2), tmp2);

    for (auto i = SZ(t)+1; i < SZ(tmp2); i++) {
        int idx = i-SZ(t);
        maxa(mx[idx-pi2[i]+1], pi2[i]);
    }

    bit.init(SZ(s));
    int ans = 0;
    for (auto i = SZ(s)-1; i >= 0; i--) {
        bit.update(i + mx[i+1], mx[i+1]);

        int pref = pi1[pi1.size()-i-1]; // for idx=i, max pref. of s that is suf. of p
        maxa(ans, pref + bit.query(i + pref));
    }
    cout << (ans) << '\n';

    return 0;
}