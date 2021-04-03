// ./easy-problem.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 1e6 + 1;
int N, Q,
    A[MN];

#define MID int mid = (l + r) / 2, lhs = i+1, rhs = i+(mid-l+1)*2;
int seg[MN*2];

vector<pair<int, int>> c_seg;
void C_S(int i, int a) {
    if (a != seg[i]) {
        c_seg.emplace_back(i, seg[i]);
        seg[i] = a;
    }
}
void undo() {
    for (auto [i, old] : c_seg)
        seg[i] = old;
    c_seg.clear();
}

int update(int q, int v, int i=1, int l=1, int r=N) {
    if (q > r || q < l) return seg[i];
    if (q == l && q == r) return seg[i] = v;
    MID;
    return seg[i] = min(update(q, v, lhs, l, mid), update(q, v, rhs, mid+1, r));
}
int skip(int ql, int qr, int i=1, int l=1, int r=N) {
    if (ql > r || qr < l) return seg[i];
    if (ql <= l && r <= qr) {
        C_S(i, INF);
        return seg[i];
    }
    MID;
    C_S(i, min(skip(ql, qr, lhs, l, mid), skip(ql, qr, rhs, mid+1, r)));
    return seg[i];
}
int query(int need, int i=1, int l=1, int r=N) {
    if (l == r) return seg[i] < need ? l : INF;
    MID;
    // printf("Q i=%d l=%d mid=%d r=%d LHS=%d rhs=%d\n", i,l,mid,r,seg[lhs],seg[rhs]);
    if (seg[lhs] < need) return query(need, lhs, l, mid);
    return query(need, rhs, mid+1, r);
}

void C(int k, int a, int b) {
    assert(a <= k && k <= b);
}

#define ENCRYPT

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    C(N, 1, 1e6);
    C(Q, 1, 1e6);
    memset(seg, 0x3f, sizeof seg);
    for (auto i = 1; i <= N; i++) {
        cin >> A[i];
        update(i, A[i]);
        C(A[i], 1, 1e9);
    }
    int lastAns = 0;
    while (Q--) {
        int T; cin >> T;
        if (T == 1) {
            int p, x; cin >> p >> x;
            p ^= lastAns; x ^= lastAns;
            C(p, 1, N);
            C(x, 1, 1e9);
            update(p, x);
        }
        else { 
            int l, r, k; cin >> l >> r >> k;
            l ^= lastAns; r ^= lastAns; k ^= lastAns;
            C(l, 1, r);
            C(r, l, N);
            C(k, 1, 1e9);
            skip(1, l-1);
            cout << (lastAns = query(k)) << '\n';
            assert(lastAns != INF);
            undo();
        }

#ifndef ENCRYPT
        lastAns = 0;
#endif
    }
}