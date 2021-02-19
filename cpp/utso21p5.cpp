// ./uts-open-21-p5-state-taxes.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 5e5 + 1;
int N, Q;

#define MID int mid = (l + r) / 2, lhs = i+1, rhs = i + (mid-l+1) * 2;
ll seg[MN*2], lazy[MN*2], salary[MN*2];
int par[MN*2];
void build(int i = 1, int l = 1, int r = N) {
    if (l == r) return;
    MID;
    par[lhs] = par[rhs] = i;
    build(lhs, l, mid); build(rhs, mid+1, r);
}
void push(int i, int l, int r) {
    if (lazy[i]) {
        seg[i] += lazy[i] * salary[i];
        if (l != r) {
            MID;
            lazy[lhs] += lazy[i];
            lazy[rhs] += lazy[i];
        }
        lazy[i] = 0;
    }
}
void update1(int ql, int qr, int qv, int i = 1, int l = 1, int r = N) {
    push(i, l, r);
    if (qr < l || ql > r) return;
    if (l >= ql && r <= qr) return void(salary[i] += qv);
    MID;
    update1(ql, qr, qv, lhs, l, mid); update1(ql, qr, qv, rhs, mid+1, r);
}
void update2(int ql, int qr, int i = 1, int l = 1, int r = N, ll add = 0) {
    push(i, l, r);
    if (qr < l || ql > r) return;
    if (l >= ql && r <= qr) {
        seg[i] += add;
        lazy[i] = 1;
        push(i, l, r);
        return;
    }
    MID;
    update2(ql, qr, lhs, l, mid, add + salary[i]); update2(ql, qr, rhs, mid+1, r, add + salary[i]);
}
ll get(int q, int i = 1, int l = 1, int r = N) {
    push(i, l, r);
    if (l == r) return seg[i];
    MID;
    if (q <= mid) return seg[i] + get(q, lhs, l, mid);
    else return seg[i] + get(q, rhs, mid+1, r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    for (int i = 1; i <= N; i++) {
        int x; cin >> x;
        update1(i, i, x);
    }

    while (Q--) {
        int T, l, r; cin >> T >> l >> r;
        if (T == 1) {
            int x; cin >> x;
            update1(l, r, x);
        }
        else
            update2(l, r);
    }

    for (int i = 1; i <= N; i++)
        cout << get(i) << ' ';
    cout << '\n';

    return 0;
}