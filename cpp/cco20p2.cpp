#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

const int MN = 2e5 + 1;
int N,
    val[MN], bit[MN], perm[MN];

void add(int x, int v) {
    for (; x <= N; x += x & -x)
        bit[x] += v;
}
ll sum(int x) {
    ll res = 0;
    for (; x; x -= x & -x)
        res += bit[x];
    return res;
}

// magical things <3
int seg[MN << 2];
int upd(int i, int l, int r, int q, int v) {
    if (l > q || r < q) return seg[i];
    if (l == q && r == q) return seg[i] = v;
    int mid = (l + r) / 2;
    return seg[i] = max(upd(i * 2, l, mid, q, v), upd(i * 2 + 1, mid + 1, r, q, v));
}
int query(int i, int l, int r, int ql, int qr) {
    if (l > qr || r < ql) return -INF;
    if (l >= ql && r <= qr) return seg[i];
    int mid = (l + r) / 2;
    return max(query(i * 2, l, mid, ql, qr), query(i * 2 + 1, mid + 1, r, ql, qr));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 1; i < N + 1; ++i) {
        cin >> val[i];
    }

    for (int i = 1; i <= N; i++) {
        upd(1, 1, N, i, val[i]);
    }
    for (int i = N; i >= 1; i--) {
        int l = 0, r = N + 1;
        while (l + 1 < r) {
            int mid = (l + r) / 2;
            if (query(1, 1, N, mid, N) >= i) // found it
                l = mid;
            else
                r = mid;
        }
        if (l == 0) {
            cout << "-1\n";
            return 0;
        }
        // cout << "i=" << i << ", l=" << l << endl;
        assert(l != 0);
        perm[l] = i;
        upd(1, 1, N, l, -INF);
    }

    ll ans = 0;
    for (int i = 1; i <= N; i++) {
        ans += sum(N) - sum(perm[i]);
        add(perm[i], 1);
    }
    cout << ans << '\n';

    return 0;
}