// ./ioi-17-p2-wiring.yml
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

#define MID int mid = (l + r) / 2, lhs = i + 1, rhs = i + (mid - l + 1) * 2;
struct Segtree {
    int N;
    vector<ll> seg, lazy;
    void init(int n0) {
        N = n0;
        seg.assign(N * 2 + 10, 0);
        lazy.assign(N * 2 + 10, 0);
    }
    void push(int i, int l, int r) {
        if (lazy[i]) {
            seg[i] += lazy[i];
            if (l != r) {
                MID;
                lazy[lhs] += lazy[i];
                lazy[rhs] += lazy[i];
            }
            lazy[i] = 0;
        }
    }
    ll _upd(int ql, int qr, ll qv, int i, int l, int r) {
        push(i, l, r);
        if (r < ql || l > qr) return seg[i];
        if (l >= ql && r <= qr) {
            lazy[i] = qv;
            push(i, l, r);
            return seg[i];
        }
        MID;
        return seg[i] = min(_upd(ql, qr, qv, lhs, l, mid), _upd(ql, qr, qv, rhs, mid + 1, r));
    }
    ll _query(int ql, int qr, int i, int l, int r) {
        if (ql > r || qr < l) return LLINF;
        push(i, l, r);
        if (l >= ql && r <= qr) return seg[i];
        MID;
        return min(_query(ql, qr, lhs, l, mid), _query(ql, qr, rhs, mid + 1, r));
    }
    void upd(int l, int r, ll v) { _upd(l, r, v, 1, 0, N); }
    ll query(int l, int r) { return _query(l, r, 1, 0, N); }
};

struct wire {
    int x, t;
    bool operator<(const wire &o) const {
        return x < o.x;
    }
};

/*
from j->i and range is j+1->i and B is the starting point of the current and E is the ending point of the previous and P is the index of the starting point of the current

Cost Function:
Let a = P-1 - j, b = i - P + 1
Cost = (a*E - sum(W[j+1..P-1])) + (sum(W[P..i]) - b*B) + max(a, b) * (B-E)

dp[i] = Cost + dp[j]
*/

const int MN = 1e5 + 5, MN2 = 2e5 + 5;
int N, M,
    num[MN2];
ll dp[MN2];
vector<wire> W;

long long min_total_length(std::vector<int> _r, std::vector<int> _b) {
    N = SZ(_r); M = SZ(_b);
    for (auto x : _r) W.pb({x, 0});
    for (auto x : _b) W.pb({x, 1});
    W.pb({-INF, 2});
    sort(all(W));
    W[0].t = W[1].t;

    int nn = N + M;
    num[0] = 1;
    for (auto i = 1; i <= nn; i++)
        num[i] = num[i - 1] + (W[i - 1].t != W[i].t);

    Segtree seg;
    int cnum = 1, stInd = 1; ll cst = -1, pen = -1;
    ll curB = 0, ws = 0;
    for (auto i = 1; i <= nn; i++) {
        // reached new block
        if (cnum != num[i]) {
            cst = W[i].x;
            pen = W[i - 1].x;

            seg.init(i - stInd); // Indices 0..(i-stInd)
            ll curA = 0, wsLeft = 0;
            for (int j = i - 1; j >= stInd - 1; j--) {
                seg.upd(curA, curA, dp[j] + (curA * pen - wsLeft) + curA * (cst - pen));
                curA++; wsLeft += W[j].x;
            }

            cnum = num[i];
            stInd = i;
            ws = 0;
            curB = 0;
        }

        auto &c = W[i];
        if (num[i] > 1) { // calc dp
            // update current values
            curB++; ws += c.x;
            seg.upd(0, curB - 1, cst - pen);
            // get dp
            dp[i] = seg.query(0, seg.N) + ws - curB * cst;
        }
        else
            dp[i] = LLINF;
    }

    return dp[nn];
}

#ifdef LOCAL
const int TC = 1,
      A[TC] = {10};
const vector<int> RR[TC] = {{1, 2, 3, 7}},
      BB[TC] = {{0, 4, 5, 9, 10}};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tc;
    cin >> tc;

    cout<<"tc="<<(tc)<<", "; cout<<"A[tc]="<<(A[tc])<<", "; cout << "RR[tc]=["; for (auto __x:RR[tc])cout<<__x<<", "; cout<<"], "; cout << "BB[tc]=["; for (auto __x:BB[tc])cout<<__x<<", "; cout<<"], "; cout << endl; // db tc,A[tc],I:RR[tc],I:BB[tc]
    int ans = min_total_length(RR[tc], BB[tc]);
    cout<<"ans="<<(ans)<<", "; cout << endl; // db ans

    return 0;
}
#endif