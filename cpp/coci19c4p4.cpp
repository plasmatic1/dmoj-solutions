// coci-19-contest-4-4-klasika.yml
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

struct Query {
    int type, x, y; // type=0-> Upd, creating node x, -1 | type=1-> Qu, query, A=x, B=y
};

struct Trie {
    set<int> ids;
    Trie* ch[2];
    Trie() { 
        ch[0] = ch[1] = nullptr;
    }
    void ins(int idx, int val, int bit = 30) {
        ids.insert(idx);
        if (bit < 0) return;
        Trie* &nxt = ch[(val >> bit) & 1];
        if (!nxt) nxt = new Trie;
        nxt->ins(idx, val, bit - 1);
    }
    int search(int l, int r, int val, int bit = 30, int res = 0) {
        if (bit < 0) return res;
        bool go = !((val >> bit) & 1);
        if (!ch[go]) go ^= 1;
        else {
            auto ptr = ch[go]->ids.lower_bound(l);
            if (ptr == ch[go]->ids.end() || *ptr > r) go ^= 1;
        }
        if (!ch[go]) return 0;
        else {
            auto ptr = ch[go]->ids.lower_bound(l);
            if (ptr == ch[go]->ids.end() || *ptr > r) return 0;
        }
        return ch[go]->search(l, r, val, bit - 1, res | (go * (1 << bit)));
    }
};

struct Ed {
    int v, w;
};

const int MN = 2e5 + 1;
int Q, N,
    dfn[MN], endDfn[MN];
vector<Ed> g[MN];
Query queries[MN];

int txor[MN];
void dfs(int c, int cxor) {
    static int curDfn = 0;
    txor[c] = cxor;
    dfn[c] = ++curDfn;
    for (auto to : g[c])
        dfs(to.v, cxor ^ to.w);
    endDfn[c] = curDfn;
}

Trie* rt = new Trie;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (Q);
    N = 1;
    
    for (auto i = 0; i < Q; i++) {
        string T; int a, b;
        cin >> T >> a >> b;
        if (T == "Add") {
            N++;
            g[a].pb({N, b});
            queries[i] = {0, N, -1};
        }
        else {
            queries[i] = {1, a, b}; }
    }

    dfs(1, 0);
    rt->ins(1, 0);

    for (auto i = 0; i < Q; i++) {
        auto &q = queries[i];
        if (q.type == 0) {
            rt->ins(dfn[q.x], txor[q.x]); }
        else {
            int ask = txor[q.x] ^ txor[q.y] ^ txor[q.y]; // XOR txor[q.y] twice for readability
            cout << (ask ^ rt->search(dfn[q.y], endDfn[q.y], ask)) << '\n'; }
    }

    return 0;
}