#include <bits/stdc++.h>
using namespace std;

int Secret(int X, int Y);

const int MN = 1e3 + 1;
int n, a[MN], seg[MN << 2];

int merge(int a, int b) {
    if (a == -1) return b;
    if (b == -1) return a;
    return Secret(a, b);
}

int build(int i, int l, int r) {
    if (l == r) return seg[i] = a[l];
    int mid = (l + r) >> 1;
    return seg[i] = merge(build(i << 1, l, mid), build(i << 1 | 1, mid + 1, r));
}

int query(int i, int l, int r, int ql, int qr) {
    if (l > qr || r < ql) return -1;
    if (l >= ql && r <= qr) return seg[i];
    int mid = (l + r) >> 1;
    return merge(query(i << 1, l, mid, ql, qr), query(i << 1 | 1, mid + 1, r, ql, qr));
}

void Init(int N, int A[]) {
    n = N;
    for (int i = 1; i <= n; i++)
        a[i] = A[i - 1];
    build(1, 1, n);
}

int Query(int L, int R) {
    return query(1, 1, n, L + 1, R + 1);
}