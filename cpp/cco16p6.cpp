// cco-16-p6-pirates.yml
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

    // Aux info
    ll val, sum, lazyAdd;
    bool lazyClear;

    Node(ll v0) : l(nullptr), r(nullptr), pri(dis(mt)), val(v0), sum(v0), lazyAdd(0), lazyClear(false) {}
};
int sz(Node *n) { return n ? n->sz : 0; }
ll sum(Node *n) { return n ? n->sum : 0; }

// clear and then add
void push(Node *n) {
    if (!n) return;
    if (n->lazyClear) {
        n->val = n->sum = 0;
        if (n->l) n->l->lazyClear = true, n->l->lazyAdd = 0;
        if (n->r) n->r->lazyClear = true, n->r->lazyAdd = 0;
        n->lazyClear = 0; 
    }
    if (n->lazyAdd) {
        n->val += n->lazyAdd;
        n->sum += n->lazyAdd * n->sz;
        if (n->l) n->l->lazyAdd += n->lazyAdd;
        if (n->r) n->r->lazyAdd += n->lazyAdd;
        n->lazyAdd = 0;
    }
}
void upd(Node *n) {
    if (!n) return;
    push(n->l); push(n->r);
    n->sz = 1 + sz(n->l) + sz(n->r);
    n->sum = n->val + sum(n->l) + sum(n->r);
}

// l-> <= key, r-> > key
// type=0->size, type=1->val
void split(Node *n, ll key, Node* &l, Node* &r, bool type) {
    if (!n) return void(l = r = nullptr);
    push(n);
    bool toLeft = type ? n->val <= key : sz(n->l) + 1 <= key;
    if (toLeft) { split(n->r, key - ((!type) * (sz(n->l) + 1)), n->r, r, type); l = n; }
    else { split(n->l, key, l, n->l, type); r = n; }
    upd(n);
}
void merge(Node* &n, Node *l, Node *r) {
    push(l); push(r);
    if (!l || !r) n = l ? l : r;
    else if (l->pri > r->pri) { merge(l->r, l->r, r); n = l; }
    else { merge(r->l, l, r->l); n = r; }
    upd(n);
}
void ins(Node* &n, ll val) {
    Node *r, *nnode = new Node(val);
    split(n, val, n, r, 1);
    merge(n, n, nnode);
    merge(n, n, r);
}
Node* kth(Node *n, int k) {
    push(n);
    int idx = sz(n->l) + 1;
    if (idx == k) return n;
    return kth(k > idx ? n->r : n->l, k - (k > idx) * idx);
}

const int MN = 1e6 + 1;
int N,
    votes[MN];
ll K;
Node *rt = nullptr;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (K);
    for (auto i = 1; i <= N; i++)
        cin >> (votes[i]);

    for (auto i = 1; i <= N; i++) {
        Node *tmp;
        split(rt, votes[i] - 1, rt, tmp, 0);
        ll req = sum(rt) + (votes[i] - 1);
        merge(rt, rt, tmp);

        if (req > K) {
            ins(rt, -1);
            cout << (-1) << '\n';
        }
        else {
            Node *l, *r;
            split(rt, votes[i] - 1, l, r, 0);
            if (l) { push(l); l->lazyAdd = 1; push(l); }
            if (r) { push(r); r->lazyClear = true; push(r); }
            merge(rt, r, l);
            ins(rt, K - req);

            cout << (K - req) << '\n';
        }
    }

    return 0;
}