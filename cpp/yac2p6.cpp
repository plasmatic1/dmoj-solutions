// ./p6-travel-budget.yml
#include <bits/stdc++.h>
#define DEBUG 1
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

template <typename T> struct Line {
    T m, b;
    Line(T m0, T b0) : m(m0), b(b0) {}
    T eval(T x) { return x * m + b; }
};
template <typename T, ll MINX = (ll)-1e6, ll MAXX = (ll)1e6> struct LiChaoTree { // Just *-1 if you want to do max lol
    using line = Line<T>;
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
    ll _query(ll x, Node *n, ll l, ll r) {
        if (!n) return LLINF;
        ll res = n->val.eval(x), mid = (l + r) / 2;
        if (l != r) {
            if (x < mid) res = min(res, _query(x, n->l, l, mid));
            else res = min(res, _query(x, n->r, mid + 1, r));
        }
        return res;
    }
    void insert(line ln) { _insert(ln, rt, MINX, MAXX); }
    ll query(ll x) { return _query(x, rt, MINX, MAXX); }
};

// template is 1-indexed
template <typename T> struct Ranks {
    vector<T> ranks;
    void init() {
        sort(ranks.begin(), ranks.end());
        ranks.resize(unique(ranks.begin(), ranks.end()) - ranks.begin());
    }
    template <typename It> void init(It st, It en) { ranks = vector<T>(st, en); init(); }
    void add(T v) { ranks.push_back(v); }
    int get(T v) { return lower_bound(ranks.begin(), ranks.end(), v) - ranks.begin() + 1; }
    int size() { return ranks.size(); }
};

using LCT = LiChaoTree<ll, 0, 1000000000+100>;

const int MN = 1e5 + 1;
int N;
ll S[MN], C[MN], D[MN], P[MN], dp[MN];
Ranks<int> rs;

#define MID int mid = (l+r) / 2, lhs = i+1, rhs = i + (mid - l + 1) * 2;
LCT seg[MN*2];
void insert(int ql, int qr, Line<ll> L, int i = 1, int l = 1, int r = N) {
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) return void(seg[i].insert(L));
    MID;
    insert(ql, qr, L, lhs, l, mid);
    insert(ql, qr, L, rhs, mid+1, r);
}
ll query(int q, int qx, int i = 1, int l = 1, int r = N) {
    if (q < l || q > r) return LLINF;
    MID;
    ll mn = seg[i].query(qx);
    if (l != r) {
        mn = min({mn,
            query(q, qx, lhs, l, mid),
            query(q, qx, rhs, mid+1, r)});

    }
    return mn;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> N;
    for (auto i = 1; i <= N; i++) {
        cin >> P[i] >> S[i] >> C[i] >> D[i];
        rs.add(P[i]);
    }
    rs.init();

    dp[1] = 0;
    for (auto i = 1; i <= N; i++) {
        if (i > 1) {
            dp[i] = query(i, P[i]);
        }
        // line 
        // dp[i] + D[i] + (x - P[i]) * C[i]
        // C[i] * x + (dp[i] + D[i] - C[i] * P[i])
        Line<ll> L(C[i], dp[i] + D[i] - C[i] * P[i]);
        int l = i, r = max(i, rs.get(P[i] + S[i] + 1) - 1);
        insert(l, r, L);
    }
    cout << (dp[N]) << '\n';

    return 0;
}