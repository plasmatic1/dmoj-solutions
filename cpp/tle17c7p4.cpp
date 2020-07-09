// tle-17-contest-7-p4-database.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define pb push_back
#define fs first
#define sn second
#define mpr make_pair
#define mtp make_tuple
// Basic type definitions
using ll = long long; using ull = unsigned long long;
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

// Hashing stuff
const ll MODS[2] = {1000000007, 1000000009}, BASE[2] = {131, 191};
ll madd(ll a, ll b, ll mod) { return (a + b) % mod; }
ll msub(ll a, ll b, ll mod) { return (a - b + mod) % mod; }
ll mmul(ll a, ll b, ll mod) { return (a * b) % mod; }
ll fpow(ll x, ll y, ll mod) {
    if (!y) return 1LL;
    return mmul(fpow(mmul(x, x, mod), y >> 1, mod), (y & 1) ? x : 1LL, mod);
}
ll mdiv(ll x, ll y, ll mod) { return mmul(x, fpow(y, mod - 2, mod), mod); }

ll comb(ll lo, ll hi) { return (hi << 32) | lo; }
ll glo(ll x) { return x & ((1LL << 32) - 1); }
ll ghi(ll x) { return x >> 32; }
ll append1(ll hsh, int val, int i) { return madd(mmul(hsh, BASE[i], MODS[i]), val, MODS[i]); }
ll append(ll hsh, int val) { return comb(append1(glo(hsh), val, 0), append1(ghi(hsh), val, 1)); } 
vector<ll> pows[2];
void init_pow(int N) {
    for (auto i = 0; i < 2; i++) {
        pows[i].resize(N + 1);
        pows[i][0] = 1LL;
        for (auto j = 1; j <= N; j++)
            pows[i][j] = mmul(pows[i][j - 1], BASE[i], MODS[i]);
    }
}
ll ghsh1(ll hr, ll hl, int sz, int i) {
    return msub(hr, mmul(pows[i][sz], hl, MODS[i]), MODS[i]);
}
ll ghsh(ll *hs, int l, int r) {
    int sz = r - l + 1;
    return comb(ghsh1(glo(hs[r]), glo(hs[l - 1]), sz, 0), ghsh1(ghi(hs[r]), ghi(hs[l - 1]), sz, 1));
}
ll concat1(ll hsh, ll hsh2, int sz, int i) { return madd(mmul(hsh, pows[i][sz], MODS[i]), hsh2, MODS[i]); }
ll concat(ll hsh, ll hsh2, int sz) { return comb(concat1(glo(hsh), glo(hsh2), sz, 0), concat1(ghi(hsh), ghi(hsh2), sz, 1)); }

const int MN = 2e5 + 1;
int N, M, Q,
    chpos[MN];
char chto[MN];
string s;

struct Node {
    Node *l, *r;
    char val; ll hsh; 
    Node(Node *l0, Node *r0, char v0, ll hsh0) : l(l0), r(r0), val(v0), hsh(hsh0) {}
};

Node* build(int l = 1, int r = M) {
    if (l == r) { return new Node(nullptr, nullptr, s[l - 1], append(0, s[l - 1])); }
    int mid = (l + r) / 2;
    auto nl = build(l, mid), nr = build(mid + 1, r);
    return new Node(nl, nr, 0, concat(nl->hsh, nr->hsh, r - mid));
}
Node* upd(Node *rt, int q, char v, int l = 1, int r = M) {
    if (l == q && r == q) { return new Node(nullptr, nullptr, v, append(0, v)); }
    int mid = (l + r) / 2;
    Node *newl = rt->l, *newr = rt->r;
    if (q <= mid) newl = upd(rt->l, q, v, l, mid);
    else newr = upd(rt->r, q, v, mid + 1, r);
    return new Node(newl, newr, 0, concat(newl->hsh, newr->hsh, r - mid));
}
char get(Node *rt, int q, int l = 1, int r = M) {
    if (l == q && r == q) return rt->val;
    int mid = (l + r) / 2;
    return q <= mid ? get(rt->l, q, l, mid) : get(rt->r, q, mid + 1, r);
}
int samePrefix(Node *rt1, Node *rt2, int l = 1, int r = M) {
    if (l == r) { return l - (rt1->val != rt2->val); }
    int mid = (l + r) / 2;
    if (rt1->l->hsh == rt2->l->hsh) return samePrefix(rt1->r, rt2->r, mid + 1, r);
    return samePrefix(rt1->l, rt2->l, l, mid);
}

Node* rts[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (s) >> (N);
    M = s.length();

    for (auto i = 2; i <= N; i++) {
        cin >> (chpos[i]) >> (chto[i]); }

    // Init DS (segtree and hash)
    init_pow(M + 10);
    rts[1] = build();
    for (auto i = 2; i <= N; i++) {
        rts[i] = upd(rts[i - 1], chpos[i], chto[i]); }

    // Sort strings
    vector<int> perm(N); iota(perm.begin(), perm.end(), 1);
    sort(perm.begin(), perm.end(), [&] (const int a, const int b) {
        int idx = samePrefix(rts[a], rts[b]) + 1;
        return idx <= M && get(rts[a], idx) < get(rts[b], idx);
    });

    cin >> (Q);
    while (Q--) {
        int stime, pos;
        cin >> stime >> pos;
        cout << (get(rts[perm[stime - 1]], pos)) << '\n';
    }

    return 0;
}