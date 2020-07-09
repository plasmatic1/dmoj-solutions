// ceoi-17-p4-building-bridges.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define pb push_back
#define fs first
#define sn second
#define mpr make_pair
#define mtp make_tuple
#define all(x) (x).begin(), (x).end()
// Basic type definitions
using ll = long long; using ull = unsigned long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<long, long>;
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
template <typename C> int sz(C &v) { return v.size(); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

template <typename T> struct Line {
    T m, b;
    Line(T m0, T b0) : m(m0), b(b0) {}
    T eval(T x) { return x * m + b; }
};
using line = Line<ll>;
const ll MINX = -1e6, MAXX = 1e6;
struct LiChao { // Just *-1 if you want to do max lol
    struct Node {
        Node *l = nullptr, *r = nullptr;
        line val{0, LLINF};
        Node(Node *l0, Node *r0, line v0) : l(l0), r(r0), val(v0) {}
    };
    Node *rt = nullptr;
    void _insert(line ln, Node *&n, ll l, ll r) {
        if (l > r) return;
        if (!n) {
            n = new Node(nullptr, nullptr, ln);
            return;
        }
        ll mid = (l + r) / 2;
        bool lDom = ln.eval(l) < n->val.eval(l), mDom = ln.eval(mid) < n->val.eval(mid);
        if (mDom) swap(ln, n->val);
        if (l == r) return; // base case
        if (lDom != mDom) _insert(ln, n->l, l, mid);
        else _insert(ln, n->r, mid + 1, r);
    }
    void insert(line ln) { _insert(ln, rt, MINX, MAXX); }
    ll _query(ll x, Node *n, ll l, ll r) {
        if (!n) return LLINF;
        ll res = n->val.eval(x), mid = (l + r) / 2;
        if (l != r) {
            if (x < mid) res = min(res, _query(x, n->l, l, mid));
            else res = min(res, _query(x, n->r, mid + 1, r));
        }
        return res;
    }
    ll query(ll x) { return _query(x, rt, MINX, MAXX); }
};

const int MN = 1e5 + 1;
int N;
ll W[MN], H[MN], psum[MN], dp[MN];
LiChao lines;

void ins(int j) {
    lines.insert(line(-2 * H[j], dp[j] + H[j] * H[j] - psum[j]));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    for (auto i = 1; i <= N; i++) {
        cin >> (H[i]); }
    for (auto i = 1; i <= N; i++) {
        cin >> (W[i]); 
        psum[i] = psum[i - 1] + W[i];
    }

    memset(dp, 0x3f, sizeof dp);
    dp[1] = 0; ins(1);
    for (auto i = 2; i <= N; i++) {
        dp[i] = H[i] * H[i] + psum[i - 1] + lines.query(H[i]);
        ins(i);
    }

    cout << (dp[N]) << '\n';

    return 0;
}