// ./ioi-11-p5-dancing-elephants.yml
#define LOCAL
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

struct Node {
    Node *ch[2], *p;
    int sum, val;
    bool rev;

    Node(int v0) {
        ch[0] = ch[1] = p = nullptr;
        val = sum = v0; rev = 0;
    }
};

void setp(Node *n, Node *p) { if (n) n->p = p; }
void setc(Node *n, bool s, Node *c) { if (n) { setp(c, n); n->ch[s] = c; } }
bool side(Node *n) { return n->p ? n == n->p->ch[1] : 0; }
bool isrt(Node *n) { return n->p ? n != n->p->ch[side(n)] : true; }

int sum(Node *n) { return n ? n->sum : 0; }

void push(Node *n) {
    if (n && n->rev) {
        swap(n->ch[0], n->ch[1]);
        if (n->ch[0]) n->ch[0]->rev ^= 1;
        if (n->ch[1]) n->ch[1]->rev ^= 1;
        n->rev = 0;
    }
}
void upd(Node *n) {
    if (n) {
        push(n->ch[0]); push(n->ch[1]);
        n->sum = sum(n->ch[0]) + sum(n->ch[1]) + n->val;
    }
}
void rot(Node *n) {
    push(n->p); push(n);
    bool s = side(n), sp = side(n->p);
    auto p = n->p, c = n->ch[!s], gp = p->p;
    if (isrt(p)) setp(n, gp); else setc(gp, sp, n);
    setc(n, !s, p); setc(p, s, c);
    upd(p); upd(n);
}
void splay(Node *n) {
    while (n && !isrt(n)) {
        if (!isrt(n->p)) {
            if (side(n->p) == side(n)) { rot(n->p); rot(n); }
            else { rot(n); rot(n); }
        } else rot(n);
    }
    push(n);
}

void access(Node *n) {
    Node *pre = nullptr;
    for (Node *c = n; c; c = c->p) {
        splay(c); c->ch[1] = pre; upd(c); pre = c; }
    splay(n);
}

// make v the child of u (v must be root)
void link(Node *u, Node *v) {
    access(u); access(v);
    setc(v, 0, u); upd(v);
}

// cut the edge (u->p, u)
void cut(Node *u) {
    access(u); setp(u->ch[0], nullptr); u->ch[0] = nullptr; upd(u);
}

ostream& operator<<(ostream& out, const pii o) {
    out << "(fs=" << o.fs << ", sn=" << o.sn << ")";
    return out;
}

// end lct; begin solution
const int MN = 150000 + 5;
int N, K, st, en,
    P[MN];
Node *lct[MN * 2];
set<pii> pos;

void addWhite(int n, int x) {
    auto p = pos.upper_bound({x, n});
    link(lct[p->sn], lct[n]);
}
pii getPre(int x, int i) { return *(--pos.find({x, i})); }
bool real(int x) { return x < N; }

void init(int n0, int l0, int X[]) {
    N = n0; K = l0;
    st = 2 * N; en = 2 * N + 1;
    for (auto i = 0; i < N; i++) {
        P[i] = X[i];
        pos.emplace(P[i], i);
        pos.emplace(P[i] + K, i + N);
    }
    pos.emplace(INT_MIN, st);
    pos.emplace(INT_MAX, en);
    for (auto i = 0; i <= en; i++)
        lct[i] = new Node(real(i));
    link(lct[0], lct[st]);
    for (auto i = 0; i < N; i++) {
        link(lct[i + N], lct[i]);
        access(lct[i]);
    }
    for (auto i = 0; i < N; i++) addWhite(i + N, P[i] + K);
}

int update(int i, int y) {
    // remove old
    auto p1 = getPre(P[i], i), p2 = getPre(P[i] + K, i + N);
    pos.erase({P[i], i});
    pos.erase({P[i] + K, i + N});
    if (!real(p1.sn)) {
        cut(lct[p1.sn]);
        addWhite(p1.sn, p1.fs);
    }
    if (!real(p2.sn)) {
        cut(lct[p2.sn]);
        addWhite(p2.sn, p2.fs);
    }
    cut(lct[i + N]);

    // make new
    P[i] = y;
    pos.emplace(y, i);
    pos.emplace(y + K, i + N);

    p1 = getPre(y, i);
    p2 = getPre(y + K, i + N);
    if (!real(p1.sn)) {
        cut(lct[p1.sn]);
        link(lct[i], lct[p1.sn]);
    }
    if (!real(p2.sn)) {
        cut(lct[p2.sn]);
        link(lct[i + N], lct[p2.sn]);
    }
    addWhite(i + N, y + K);
    
    // print answer
    access(lct[st]);
    return lct[st]->sum;
}

#ifdef LOCAL
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, L, Q;
    cin >> N >> L >> Q;
    int X[N];
    for (auto i = 0; i < N; i++)
        cin >> (X[i]);
    init(N, L, X);
    for (auto i = 0; i < Q; i++) {
        int a, b;
        cin >> a >> b;
        cout << (update(a, b)) << '\n';
    }

    return 0;
}
#endif