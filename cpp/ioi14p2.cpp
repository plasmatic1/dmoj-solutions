// ./ioi-14-p2-wall.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

const int MN = 2e6+1;
const pii DEF = {-INF, INF};
#define MID int mid = (l+r) / 2, lhs = i+1, rhs = i+(mid-l+1)*2
pii lazy[MN*2]; int seg[MN*2];

pii merge(const pii a, const pii b) {
    return {min(max(a.first, b.first), b.second), min(max(a.second, b.first), b.second)};
}
void push(int i, int l, int r) {
    if (lazy[i] != DEF) {
        seg[i] = min(max(lazy[i].first, seg[i]), lazy[i].second);
        if (l != r) {
            MID;
            lazy[lhs] = merge(lazy[lhs], lazy[i]);
            lazy[rhs] = merge(lazy[rhs], lazy[i]);
        }
        lazy[i] = DEF;
    }
}
void update(int op, int ql, int qr, int qv, int i, int l, int r) {
    push(i, l, r);
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) {
        if (op == 1) lazy[i] = {qv, INF};
        else lazy[i] = {-INF, qv};
        return;
    }
    MID;
    update(op, ql, qr, qv, lhs, l, mid); update(op, ql, qr, qv, rhs, mid+1, r);
}
void build(int ans[], int i, int l, int r) {
    push(i, l, r);
    if (l == r) return void(ans[l] = seg[i]);
    MID;
    build(ans, lhs, l, mid); build(ans, rhs, mid+1, r);
}

void buildWall(int n, int q, int op[], int L[], int R[], int H[], int ans[]) {
    fill(lazy, lazy+n*2, DEF);
    for (auto i = 0; i < q; i++)
        update(op[i], L[i], R[i], H[i], 0, 0, n-1);
    build(ans, 0, 0, n-1);
}

#ifdef LOCAL
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    int o[q], l[q], r[q], h[q], ans[n];
    for (auto i = 0; i < q; i++)
        cin >> o[i] >> l[i] >> r[i] >> h[i];
    buildWall(n, q, o, l, r, h, ans);
    for (auto i = 0; i < n; i++) cout << ans[i] << '\n';

    return 0;
}
#endif