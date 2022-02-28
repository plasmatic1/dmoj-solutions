#include "bits/stdc++.h"
using namespace std;

using P = pair<string, string>;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 1e6 + 10;
int N, C;

ll cnt[MN];

// segtree
#define MID int mid = (l+r) / 2, lhs = i+1, rhs = i+(mid-l+1)*2;
ll seg[MN*2], lazy[MN*2];
void push(int i, int l, int r) {
    if (lazy[i]) {
        seg[i] += lazy[i] * (r - l + 1);
        if (l != r) {
            MID;
            lazy[lhs] += lazy[i];
            lazy[rhs] += lazy[i];
        }
        lazy[i] = 0;
    }
}
ll query(int ql, int qr, int i=1, int l=0, int r=N-1) {
    if (ql > r || qr < l) return 0LL;
    push(i, l, r);
    if (ql <= l && r <= qr) return seg[i];
    MID;
    return query(ql, qr, lhs, l, mid) + query(ql, qr, rhs, mid+1, r);
}
ll update(int ql, int qr, ll qv, int i=1, int l=0, int r=N-1) {
    push(i, l, r);
    if (ql > r || qr < l) return seg[i];
    if (ql <= l && r <= qr) {
        lazy[i] += qv;
        push(i, l, r);
        return seg[i];
    }
    MID;
    return seg[i] = update(ql, qr, qv, lhs, l, mid) + update(ql, qr, qv, rhs, mid+1, r);
}
// segtree

vector<int> A;

int getL(int x) {
    return lower_bound(A.begin(), A.end(), x) - A.begin();
}

int getR(int x) {
    return upper_bound(A.begin(), A.end(), x) - A.begin() - 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> C;
    for (auto i = 0; i < N; i++) {
        int x; cin >> x;
        cnt[x]++;
        A.push_back(x);
    }
    sort(A.begin(), A.end());
    
    ll ans = 0;
    int mxdis = (C - 1) / 2; // L = mxdis

    for (auto i = 0; i < C; i++) {
        int l, r;
        if (i + mxdis < C) {
            l = getL(0);
            r = getR(i - C + 2 * mxdis);
            update(l, r, cnt[i + mxdis]);
        }

        l = getL(max(0, i-mxdis));
        r = getR(i-1);
        ll q = query(l, r);
        ans += q * cnt[i];
    }

    cout << ans << '\n';

    return 0;
}