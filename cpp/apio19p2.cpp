// ./apio-19-p2-bridges.yml
#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt"
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

using us = unsigned short;
struct query {
    us a; int b, i;
    bool operator<(const query &o) const {
        return b > o.b;
    }
};
struct edge {
    us a, b; int c, i, qo;
    bool operator<(const edge &o) const {
        return c < o.c;
    }
};
bool cmpi(const edge a, const edge b) {
    return a.qo > b.qo;
}
ostream& operator<<(ostream& out, const query o) {
    out << "(a=" << o.a << ", b=" << o.b << ", i=" << o.i << ")";
    return out;
}
ostream& operator<<(ostream& out, const edge o) {
    out << "(a=" << o.a << ", b=" << o.b << ", c=" << o.c << ", i=" << o.i << ", qo=" << o.qo << ")";
    return out;
}

struct gedge {
    int c, i;
    bool operator<(const gedge &o) const {
        return c == o.c ? i < o.i : c > o.c;
    }
};

const int MN = 5e4 + 1, MQ = 1e5 + 1, BSZ = 4*317;
// const int MN = 5e4 + 1, MQ = 1e5 + 1, BSZ = 4;
int N, M, Q;
set<gedge> edges;

struct DSU {
    us dsu[MN], sz[MN];
    void init(int N) {
        iota(dsu, dsu + N + 1, 0);
        fill(sz, sz + N + 1, 1);
    }
    us rt(us x) { return dsu[x] == x ? x : dsu[x] = rt(dsu[x]); }
    void merge(us x, us y) { // x -> y
        x = rt(x); y = rt(y);
        if (x == y) return;
        if (sz[y] > sz[x]) swap(x, y);
        sz[x] += sz[y];
        dsu[y] = x;
    }
    us getsz(us x) { return sz[rt(x)]; }
    bool same(us x, us y) { return rt(x) == rt(y); }
};

int W[MQ]; us A[MQ], B[MQ], ans[MQ];
bool rem[MQ];
DSU dsu;

// per query
bool cuse[MQ], vis[MN];
vector<us> found, tmpg[MN];
int qid[MN];

us stk[MN], spt = 0;
us dfs(us c, int cqid) {
    us res = 0;
    stk[spt++] = c;
    vis[c] = true;
    while (spt) {
        us c = stk[--spt];
        res += dsu.sz[c];
        found.pb(c);
        if (qid[c] != cqid) {
            qid[c] = cqid;
            tmpg[c].clear();
        }
        for (us to : tmpg[c]) {
            if (!vis[to]) {
                vis[to] = true;
                stk[spt++] = to;
            }
        }
    }
    return res;
}

// for block
vector<query> qs;
vector<edge> uedges;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M);
    for (auto i = 1; i <= M; i++) {
        us a, b; int c;
        cin >> a >> b >> c;
        edges.insert({c, i});
        W[i] = c; A[i] = a; B[i] = b;
    }

    cin >> (Q);
    for (auto i = 0; i < Q; i += BSZ) {
        // collect queries
        for (auto j = i; j < min(Q, i + BSZ); j++) {
            int t, a, b;
            cin >> t >> a >> b;

            if (t == 1) {
                uedges.pb({A[a], B[a], b, a, j});
                if (!rem[a] && b < W[a]) {
                    uedges.pb({A[a], B[a], W[a], a, -INF});
                    rem[a] = true;
                }
            }
            else if (t == 2) 
                qs.pb({(us)a, b, j});
        }
        sort(all(qs));
        sort(all(uedges), cmpi);

        // solve queries
        dsu.init(N);
        auto ptr = edges.begin();
        for (auto &q : qs) {
            while (ptr != edges.end() && (rem[ptr->i] || ptr->c >= q.b)) {
                if (!rem[ptr->i])
                    dsu.merge(A[ptr->i], B[ptr->i]);
                ptr++;
            }

            // build graph man
            for (auto &e : uedges) {
                if (!cuse[e.i] && e.qo < q.i) {
                    cuse[e.i] = true;
                    if (e.c >= q.b) {
                        us a = dsu.rt(e.a), b = dsu.rt(e.b);
                        if (a != b) {
                            if (qid[a] != q.i) {
                                qid[a] = q.i;
                                tmpg[a].clear();
                            }
                            if (qid[b] != q.i) {
                                qid[b] = q.i;
                                tmpg[b].clear();
                            }
                            tmpg[a].pb(b);
                            tmpg[b].pb(a);
                        }
                    }
                }
            }

            // bruh
            us cans = dfs(dsu.rt(q.a), q.i);
            ans[q.i] = cans;

            // cleanup per query
            for (auto &e : uedges) {
                if (cuse[e.i]) {
                    cuse[e.i] = false;
                }
            }
            for (auto &x : found)
                vis[x] = false;
            found.clear();
        }

        // undo and reset DS
        for (auto it = uedges.rbegin(); it != uedges.rend(); it++) {
            auto &e = *it;
            if (W[e.i] != e.c) {
                edges.erase(edges.find({W[e.i], e.i}));
                W[e.i] = e.c;
                edges.insert({W[e.i], e.i});
            }
            rem[e.i] = false;
        }

        qs.clear();
        uedges.clear();
    }

    for (auto i = 0; i < Q; i++)
        if (ans[i])
            cout << (ans[i]) << '\n';

    return 0;
}