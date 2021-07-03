// ./cco-21-p3-through-another-maze-darkly.yml
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

const int MN = 8e5 + 1;
int N, Q,
    in[MN], out[MN], par[MN], parIdx[MN];
vector<int> g[MN];

// get first time appears
int fst[MN];
vector<int> seq;
void dfs(int c, int p) {
    par[c] = p;
    for (auto to : g[c]) {
        if (to != p)
            dfs(to, c);
    }
}
void getTour(int c, int p) {
    in[c] = SZ(seq);
    seq.pb(c);
    for (auto i = 0; i < SZ(g[c]); i++) {
        int to = g[c][(parIdx[c]+i) % SZ(g[c])];
        if (to != p) {
            getTour(to, c);
            seq.pb(c);
        }
    }
    out[c] = SZ(seq);
}
void dfs2(int c, int p) {
    for (auto i = 0; i < parIdx[c]; i++) {
        int to = g[c][i];
        fst[to] = fst[c];
        dfs2(to, c);
    }
    for (auto i = parIdx[c]+1; i < SZ(g[c]); i++) {
        int to = g[c][i];
        fst[to] = fst[c]+1;
        dfs2(to, c);
    }
}

// Bsearch+BIT 
const int BMN = MN*2;
int bit[BMN];
void add(int x, int v) {
    for (; x < BMN; x += x & -x)
        bit[x] += v;
}
int search(int k) {
    int idx = 0, alt = 0;
    for (int cbit = 1048576; cbit; cbit >>= 1) {
        int altidx = idx | cbit;
        if (altidx < BMN && alt + bit[altidx] < k) {
            idx = altidx;
            alt += bit[altidx];
        }
    }
    return idx+1;
}

// offline?
vector<int> addAt[MN];
pair<ll, int> qs[MN];
int ans[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    for (auto i = 1; i <= N; i++) {
        int n; cin >> n;
        for (auto j = 0; j < n; j++) {
            int x; cin >> x;
            g[i].pb(x);
        }
        rotate(g[i].begin(), g[i].begin()+1, g[i].end());
    }
    for (auto i = 0; i < Q; i++) {
        ll k; cin >> k; k++;
        qs[i] = {k, i};
    }
    sort(qs, qs+Q);

    // preprocessing: par info
    dfs(1, -1); 
    for (auto i = 1; i <= N; i++) 
        parIdx[i] = find(all(g[i]), par[i]) - g[i].begin();
    // preprocessing: euler tour
    seq.pb(-1);
    getTour(1, -1);
    seq.pop_back(); // remove final C
    // preprocessing: first tour
    dfs2(1, -1);
    int maxLoop = 0;
    for (auto i = 1; i <= N; i++) {
        addAt[fst[i]].pb(i);
        maxa(maxLoop, fst[i]);
    }

    // answer queries in offline order
    int ptr = 0, ccnt = 0;
    ll cur = 0;
    for (auto i = 0; i <= maxLoop; i++) { // first few euler tours
        for (auto n : addAt[i]) {
            add(in[n], 1);
            ccnt++;
            if (out[n] < SZ(seq)) {
                add(out[n], 1);
                ccnt++;
            }
        }

        while (ptr < Q && qs[ptr].first <= cur+ccnt) {
            auto [k, idx] = qs[ptr];
            ans[idx] = seq[search(k-cur)];

            ptr++;
        }
        cur += ccnt;
    }
    while (ptr < Q) { // continuous loop
        auto [k, idx] = qs[ptr]; k -= cur;
        ans[idx] = seq[(k-1) % ccnt + 1];

        ptr++;
    }

    for (auto i = 0; i < Q; i++)
        cout << (ans[i]) << '\n';

    return 0;
}