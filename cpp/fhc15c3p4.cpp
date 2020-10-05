// ./fox-rocks.yml
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
using ll = long long; using ull = unsigned long long; 
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

// using ld = long double;
using ld = double;
using Mat = vector<vector<ld>>;
using Vec = vector<ld>;

// matrix utils
Mat make(int N, ld v = 0) { return Mat(N, Vec(N, v)); }
void reset(Mat &M, ld v = 0) {
    int N = SZ(M);
    for (auto i = 0; i < N; i++)
        for (auto j = 0; j < N; j++)
            M[i][j] = v;
}
void reset(Vec &v, ld vv = 0) {
    int N = SZ(v);
    for (auto i = 0; i < N; i++) v[i] = vv;
}
void mul(Mat &f, Mat &g, Mat &res) {
    reset(res);
    int N = SZ(f);
    for (auto i = 0; i < N; i++)
        for (auto j = 0; j < N; j++)
            for (auto k = 0; k < N; k++)
                res[i][j] += f[i][k] * g[k][j];
}
void mul(Vec &v, Mat &M, Vec &res) {
    reset(res);
    int N = SZ(v);
    for (auto i = 0; i < N; i++)
        for (auto j = 0; j < N; j++)
            res[i] += M[i][j] * v[j];
}
// simulate an infinite number of runs of a matrix
const int TRIALS = 31;
void extend(Mat &m) {
    int N = SZ(m);
    Mat tmp = make(N);
    for (auto i = 0; i < TRIALS; i++) {
        mul(m, m, tmp);
        tmp.swap(m);
    }
}

const int MN = 50004 + 1, MG = MN / 4 + 1;
int N, M, Q;
set<pii> g[MN];

Mat seg[MG * 2];
#define MID int mid = (l + r) / 2, lhs = i + 1, rhs = i + (mid - l + 1) * 2;

// segtree
int finalBlockNo;
void build(int i = 1, int l = 0, int r = finalBlockNo) {
    seg[i] = make(4);
    for (auto j = 0; j < 4; j++)
        seg[i][j][j] = 1;
    if (l == r) return;
    MID;
    build(lhs, l, mid); build(rhs, mid + 1, r);
}
void update(int q, Mat &m, int i = 1, int l = 0, int r = finalBlockNo) {
    if (l > q || r < q) return;
    if (l == q && r == q) return void(seg[i] = m);
    MID;
    update(q, m, lhs, l, mid); update(q, m, rhs, mid + 1, r);
    mul(seg[rhs], seg[lhs], seg[i]);
}
Mat query(int ql, int qr, int i = 1, int l = 0, int r = finalBlockNo) {
    if (ql > r || qr < l) {
        Mat res = make(4); 
        for (auto i = 0; i < 4; i++) res[i][i] = 1;
        return res;
    }
    if (l >= ql && r <= qr) return seg[i];
    MID;
    Mat res = make(4), lmat = query(ql, qr, lhs, l, mid), rmat = query(ql, qr, rhs, mid + 1, r);
    mul(rmat, lmat, res);
    return res;
}

// recalculate block
void fix(int bk) {
    // calculate probability of exiting the block on each node given the probabilities of entering the block on each node
    Mat nxt = make(8);
    for (auto i = 4; i < 8; i++)
        nxt[i][i] = 1;
    for (auto i = 4*bk; i < 4*(bk+1); i++) {
        ld sum = 0;
        for (auto to : g[i]) sum += to.sn;
        for (auto to : g[i]) {
            ld p = to.sn / sum;
            if (to.fs / 4 == bk) // same block
                nxt[to.fs % 4][i % 4] += p;
            else // exit current block
                nxt[i % 4 + 4][i % 4] += p;
        }
    }
    extend(nxt);

    // calculate destination probabilities after exiting block
    Mat selout = make(4), out = make(4);
    Vec v(8), tmp(8);
    for (auto i = 4*bk; i < 4*(bk+1); i++) {
        ld sum = 0;
        for (auto to : g[i])
            if (to.fs / 4 == bk + 1)
                sum += to.sn;
        for (auto to : g[i]) {
            if (to.fs / 4 == bk + 1) {
                ld p = to.sn / sum;
                out[to.fs % 4][i % 4] += p;
            }
        }

        reset(v); v[i % 4] = 1;
        mul(v, nxt, tmp);
        for (auto j = 0; j < 4; j++)
            selout[j][i % 4] = tmp[4 + j];
    }

    // update segtree
    Mat finalMat = make(4);
    mul(out, selout, finalMat);
    update(bk, finalMat);
}

void solve() {
    // input
    cin >> (N) >> (M) >> (Q);
    for (auto i = 0; i < M; i++) {
        int a, b, w;
        cin >> a >> b >> w; // a--; b--;
        g[a].emplace(b, w);
    }
    while (N % 4) N++;

    // init and build segtree
    finalBlockNo = N/4 - 1;
    build();
    for (auto i = 0; i < N/4; i++)
        fix(i);

    // answer queries
    while (Q--) {
        int T, x, y;
        cin >> T >> x >> y; // x--; y--;
        if (T == 1) {
            int z;
            cin >> z;
            g[x].emplace(y, z);
            fix(x / 4);
        }
        else if (T == 2) {
            g[x].erase(g[x].lower_bound(mpr(y, -1)));
            fix(x / 4);
        }
        else {
            if (x > y && x / 4 != y / 4) {
                cout << 0. << ' ';
                continue;
            }
            // pre->possibilitiy of moving from BLOCK(x) to BLOCK(y)
            // here->possibility of hitting y by looping around after reaching BLOCK(y)
            Mat pre = query(x / 4, y / 4 - 1), here = make(4);
            int bk = y / 4;
            for (auto i = 4*bk; i < 4*(bk+1); i++) {
                if (i == y) {
                    here[i % 4][i % 4] += 1;
                    continue;
                }
                ld sum = 0;
                for (auto &to : g[i]) sum += to.sn;
                for (auto &to : g[i]) {
                    ld p = to.sn / sum;
                    if (to.fs / 4 == bk)
                        here[to.fs % 4][i % 4] += p;
                }
            }
            extend(here);

            // Calculate final answer
            Mat opm = make(4); mul(here, pre, opm);
            Vec v(4), res(4); v[x % 4] = 1;
            mul(v, opm, res);
            cout << res[y % 4] << ' ';
        }
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << fixed << setprecision(6);

    int T;
    cin >> T;
    for (int caseno = 1; caseno <= T; caseno++) {
        // Input
       
        cout << "Case #" << caseno << ": ";
        solve();

        // Reset
#ifndef LOCAL
        cerr << "Done case #" << caseno << endl;
#endif

        for (auto i = 0; i < N; i++)
            g[i].clear();
    }

    return 0;
}