// s5.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a*b/gcd(a,b); }

const int MN = 150001;
int N, M,
    L[MN], R[MN], Z[MN];

void bad() {
    cout << "Impossible\n";
    exit(0);
}

ll seg1[MN*2], seg2[MN*2];
#define MID int mid = (l + r) / 2, lhs = i+1, rhs = i + (mid-l+1)*2;

void check(ll v) { if (v > 1e9) bad(); }
void update(int ql, int qr, int qv, int i=1, int l=1, int r=N) {
    if (ql > r || qr < l) return;
    if (l >= ql && r <= qr) {
        seg1[i] = lcm(seg1[i], qv);
        check(seg1[i]);
        return;
    }
    MID;
    update(ql, qr, qv, lhs, l, mid);
    update(ql, qr, qv, rhs, mid+1, r);
}
ll build(int i=1, int l=1, int r=N, ll cur=1) {
    cur = lcm(cur, seg1[i]);
    check(cur);
    if (l == r) return seg2[i] = cur;
    MID;
    return seg2[i] = gcd(build(lhs, l, mid, cur), build(rhs, mid+1, r, cur));
}
ll query(int ql, int qr, int i=1, int l=1, int r=N) {
    if (ql > r || qr < l) return 0;
    if (l >= ql && r <= qr) return seg2[i];
    MID;
    return gcd(query(ql, qr, lhs, l, mid), query(ql, qr, rhs, mid+1, r));
}
ll get(int q, int i=1, int l=1, int r=N) {
    if (l == r) return seg2[i];
    MID;
    if (q <= mid) return get(q, lhs, l, mid);
    else return get(q, rhs, mid+1, r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    fill(seg1, seg1+MN*2, 1);
    for (auto i = 0; i < M; i++) {
        cin >> L[i] >> R[i] >> Z[i];
        update(L[i], R[i], Z[i]);
    }
    build();

    for (auto i = 0; i < M; i++) {
        if (query(L[i], R[i]) != Z[i])
            bad();
    }

    for (auto i = 1; i <= N; i++)
        cout << get(i) << ' ';
    cout << '\n';

    return 0;
}