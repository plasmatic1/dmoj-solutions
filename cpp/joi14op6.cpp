#include <bits/stdc++.h>
using namespace std;

int Secret(int X, int Y);

const int MN = 1001, LG = 12;
int N,
    tb[LG][MN], val[MN];

// divide and conquer tree
void precalc(int layer, int l, int r) {
    if (l > r) return;
    if (l == r) { tb[layer][l] = val[l]; return; }
    int mid = (l + r) / 2;

    // assign
    tb[layer][mid + 1] = val[mid + 1]; tb[layer][mid] = val[mid];
    for (int i = mid + 2; i <= r; i++)
        tb[layer][i] = Secret(tb[layer][i - 1], val[i]);
    for (int i = mid - 1; i >= l; i--)
        tb[layer][i] = Secret(val[i], tb[layer][i + 1]);
    
    // continue
    precalc(layer + 1, l, mid - 1); precalc(layer + 1, mid + 1, r);
}

int query(int layer, int l, int r, int ql, int qr) {
    int mid = (l + r) / 2;
    if (ql <= mid && qr >= mid) {
        int res = tb[layer][ql];
        if (qr > mid) res = Secret(res, tb[layer][qr]);
        return res;
    }
    else if (qr < mid)
        return query(layer + 1, l, mid - 1, ql, qr);
    else if (ql > mid)
        return query(layer + 1, mid + 1, r, ql, qr);
    assert(0);
}

void Init(int N0, int A[]) {
    N = N0;
    copy(A, A + N, val);
    precalc(0, 0, N - 1);
}

int Query(int L, int R) {
    if (L == R) return val[L];
    return query(0, 0, N - 1, L, R);
}