// apio-12-p1-dispatching.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define pb push_back
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
template <typename C> int SZ(C &v) { return v.size(); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

mt19937 mt(04072020);
uniform_int_distribution<int> dis(INT_MIN, INT_MAX);

struct Node {
    Node *l, *r;
    int pri, sz;
    ll val, sum;
    Node(ll v0) : l(nullptr), r(nullptr), pri(dis(mt)), sz(1), val(v0), sum(v0) {}
    ~Node() {
        if (l) delete l;
        if (r) delete r;
    }
};

ll sum(Node *n) { return n ? n->sum : 0; }
ll sz(Node *n) { return n ? n->sz : 0; }

void upd(Node *n) {
    if (n) {
        n->sz = sz(n->l) + sz(n->r) + 1;
        n->sum = sum(n->l) + sum(n->r) + n->val;
    }
}
void split(Node *n, ll key, Node *&l, Node *&r) {
    if (!n) return void(l = r = nullptr); 
    if (key >= n->val) { split(n->r, key, n->r, r); l = n; }
    else { split(n->l, key, l, n->l); r = n; }
    upd(n);
}
void merge(Node *&n, Node *l, Node *r) {
    if (!l || !r) n = l ? l : r;
    else if (l->pri > r->pri) { merge(l->r, l->r, r); n = l; }
    else { merge(r->l, l, r->l); n = r; }
    upd(n);
}
void ins(Node *&rt, ll val) {
    Node *newv = new Node(val), *tmp;
    split(rt, val, rt, tmp);
    merge(rt, rt, newv);
    merge(rt, rt, tmp);
}
int getCnt(Node *n, ll maxV, int cadd = 0) {
    if (!n) return cadd;
    ll lsum = sum(n->l) + n->val, ladd = sz(n->l) + 1;
    if (maxV < lsum) return getCnt(n->l, maxV, cadd);
    else if (maxV > lsum) return getCnt(n->r, maxV - lsum, cadd + ladd);
    else return cadd + ladd;
}
void addAll(Node *rt, Node *&to) {
    if (!rt) return;
    ins(to, rt->val);
    addAll(rt->l, to); addAll(rt->r, to);
}

void ptree(Node *rt) {
    if (!rt) return;
    ptree(rt->l); cout << rt->val << ", "; ptree(rt->r);
}

const int MN = 1e5 + 1;
int N;
ll M, 
   C[MN], L[MN];
vector<int> g[MN];
Node* cost[MN];

ll ans = 0;
void dfs(int c) {
    ins(cost[c], C[c]);
    for (int to : g[c]) {
        dfs(to);
        if (sz(cost[to]) > sz(cost[c])) swap(cost[to], cost[c]); 
        addAll(cost[to], cost[c]);
        delete cost[to];
    }

    ll cans = L[c] * getCnt(cost[c], M);
    maxa(ans, cans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M);
    for (auto i = 1; i <= N; i++) {
        int p;
        cin >> p;
        cin >> (C[i]) >> (L[i]);

        if (p) g[p].pb(i);
    }

    dfs(1);
    cout << (ans) << '\n';

    return 0;
}