// ./ioi-15-p4-horses-standard-io.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int S = 1 << 20;
struct Segtree {
    ll seg[S*2];
    function<ll(ll, ll)> C;
    Segtree(decltype(C) C0) : C(C0) {}
    void init(int v) {
        fill(seg, seg+S*2, v);
    }
    void update(int x, ll v) {
        seg[x += S-1] = v;
        for (x >>= 1; x; x >>= 1)
            seg[x] = C(seg[x*2], seg[x*2+1]);
    }
    ll query(int l, int r) {
        ll res = 1LL;
        for (l += S-1, r += S-1; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) res = C(res, seg[l++]);
            if (!(r & 1)) res = C(res, seg[r--]);
        }
        return res;
    }
};

const ll MOD = 1e9 + 7;
const int MN = 5e5 + 1;
int N,
    X[MN], Y[MN];

Segtree prodMax([] (ll a, ll b) { return min(1000000001LL, a*b); }),
        res([] (ll a, ll b) { return (a*b) % MOD; }),
        yMax([] (ll a, ll b) { return max(a, b); });
set<int, greater<int>> non1;

int query() {
    // find "start" (must be at most log(1e9) non-one Xs)
    int start = 0;
    for (auto x : non1) {
        if (prodMax.query(x+1, N) <= 1000000000) start = x;
        else break;
    }

    // process each non1 in O(logN) time with RMQ
    int pre = N+1, bestAns = -1;
    ll best = -LLINF;
    for (auto x : non1) {
        ll yv = yMax.query(x, pre-1), alt = prodMax.query(start+1, x) * yv;
        if (alt > best) {
            best = alt;
            bestAns = (res.query(1, x) * yv) % MOD;
        }

        pre = x;
        if (x == start) break; // last one
    }
    return bestAns;
}

void changeX(int x, int v) {
    int pre = X[x-1];
    if (x == 1 || pre != 1) non1.erase(x);
    prodMax.update(x, v);
    res.update(x, v);
    if (x == 1 || v != 1) non1.insert(x);
    X[x-1] = v;
}

int init(int N0, int X0[], int Y0[]) {
    N = N0;
    copy(Y0, Y0+N, Y);

    // set initial state
    prodMax.init(1);
    res.init(1);
    fill(X, X+N, 1); // initially

    // do initial setting as updates
    for (auto i = 0; i < N; i++) {
        changeX(i+1, X0[i]);
        yMax.update(i+1, Y[i]);
    }

    return query();
}

int updateX(int pos, int val) {
    changeX(pos+1, val);
    return query();
}

int updateY(int pos, int val) {
    Y[pos] = val;
    yMax.update(pos+1, Y[pos]);
    return query();
}

#define LOCAL
#ifdef LOCAL
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N; cin >> N;
    int X[N], Y[N];
    for (auto i = 0; i < N; i++) cin >> X[i];
    for (auto i = 0; i < N; i++) cin >> Y[i];
    cout << init(N, X, Y) << '\n';

    int Q; cin >> Q;
    while (Q--) {
        int t, x, y; cin >> t >> x >> y;
        if (t == 1) cout << updateX(x, y) << '\n';
        if (t == 2) cout << updateY(x, y) << '\n';
    }

    return 0;
}
#endif