// ./dmopc-15-contest-7-p6-a-very-very-original-problem.yml
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

struct suf {
    int r1, r2, idx;
    bool operator<(const suf &o) const {
        return r1 == o.r1 ? r2 < o.r2 : r1 < o.r1;
    }
};
ostream& operator<<(ostream& out, const suf o) {
    out << "(idx=" << o.idx << ", r1=" << o.r1 << ", r2=" << o.r2 << ")";
    return out;
}

const int MN = 1e5 + 1, MN2 = MN * 2;
int N;
string s;

// suffix arr
int nn,
    idx[MN2], lcp[MN2];
string t;
suf ss[MN2];

// sptable
const int LG = 18;
int tb[LG][MN2];
void init() {
    for (auto i = 1; i < LG; i++) {
        int jmp = 1 << (i - 1), end = nn - (1 << i) + 1;
        for (auto j = 1; j <= end; j++)
            tb[i][j] = min(tb[i - 1][j], tb[i - 1][j + jmp]);
    }
}
int getLCP(int l, int r) { // l,r are indices, not r1nge bounds
    l = idx[l]; r = idx[r];
    if (l > r) swap(l, r);
    r--;
    int bit = __lg(r - l + 1);
    return min(tb[bit][l], tb[bit][r - (1 << bit) + 1]);
}

/*
 * abcdcef$fecdcba
 *
 * odd len: start at d (i=4)
 * LCP(i-1, N+1+(N-i))
 *
 * even len: start at d (i=4)
 * LCP(i-1, N+1+(N-i)+1)
 */

ll fwd[MN], rev[MN];
void compute(ll ans[MN], bool make_psum) {
    // get string t (for palindromes)
    t = s;
    reverse(all(t));
    t = s + "$" + t;

    // ==== build SA and sptable
    // Build SA
    nn = SZ(t);
    for (auto i = 0; i < nn; i++)
        ss[i] = {t[i], -1, i};
    sort(ss, ss + nn);
    for (auto i = 1; i <= nn; i *= 2) {
        int ctr = -1;
        suf pre = {-INF, -INF, -INF};
        for (auto j = 0; j < nn; j++) {
            ctr += pre < ss[j];
            pre = ss[j];
            ss[j].r1 = ctr;
            idx[ss[j].idx] = j;
        }
        for (auto j = 0; j < nn; j++) {
            int nxt = ss[j].idx + i;
            ss[j].r2 = nxt < nn ? ss[idx[nxt]].r1 : -1;
        }
        sort(ss, ss + nn);
    }
    // Build LCP array
    for (auto i = 0; i < nn; i++)
        idx[ss[i].idx] = i;
    int pre = 0;
    for (auto i = 0; i < nn; i++) {
        if (idx[i] < nn-1) {
            auto &c = ss[idx[i]], &n = ss[idx[i]+1];
            while (c.idx + pre < nn && n.idx + pre < nn && t[c.idx+pre] == t[n.idx+pre]) pre++;
            lcp[idx[i]] = pre;
            pre -= bool(pre);
        }
        else
            lcp[idx[i]] = 0;
    }
    // Build sptable
    copy(lcp, lcp + nn, tb[0]);
    init();

    // compute ans
    for (auto i = 1; i <= N; i++) {
        // odd palindrome
        int len = getLCP(i - 1, N + 1 + (N - i));
        ans[i]++;
        if (i + len <= N) ans[i+len]--;
        // even palindrome
        if (i > 1) {
            len = getLCP(i - 1, N + 1 + (N - i) + 1);
            ans[i]++;
            if (i + len <= N) ans[i+len]--;
        }
    }

    partial_sum(ans, ans + N + 1, ans);
    if (make_psum) partial_sum(ans, ans + N + 1, ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (s);
    N = SZ(s);

    compute(fwd, false);
    reverse(all(s));
    compute(rev, true);
    reverse(rev + 1, rev + N + 1);

    ll ans = 0;
    for (auto i = 1; i < N; i++)
        ans += fwd[i] * rev[i+1];
    cout << (ans) << '\n';

    return 0;
}