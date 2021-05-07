// ./ioi-13-p3-wombats.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MR = 5001, MC = 201, BRUTE_TH = 8;
int R, C,
    H[MR][MC], V[MR][MC];

// brute force DP (to reduce # of nodes)
void brute(int r1, int r2, int res[MC][MC]) {
    for (auto i = 0; i < C; i++) {
        int cdp[MC], ndp[MC];
        cdp[i] = 0;
        for (auto j = i+1; j < C; j++) cdp[j] = cdp[j-1] + H[r1][j-1];
        for (auto j = i-1; j >= 0; j--) cdp[j] = cdp[j+1] + H[r1][j];
        for (auto j = 0; j < C; j++) cdp[j] += V[r1][j];

        for (auto j = r1+1; j <= r2; j++) {
            memset(ndp, 0x3f, sizeof ndp);

            int best = INF;
            for (auto k = 0; k < C; k++) {
                if (k > 0) best += H[j][k-1];
                best = min(best, cdp[k]);
                ndp[k] = best;
            }
            best = INF;
            for (auto k = C-1; k >= 0; k--) {
                if (k < C-1) best += H[j][k];
                best = min(best, cdp[k]);
                ndp[k] = min(ndp[k], best);
            }
            for (auto k = 0; k < C; k++) ndp[k] += V[j][k];

            swap(cdp, ndp);
        }

        copy(cdp, cdp+C, res[i]);
    }
}

// segtree
int seg[(MR*2/BRUTE_TH)+1][MC][MC];
void comb(int A[MC][MC], int B[MC][MC], int res[MC][MC]) { // combiner
    static int opt[MC][MC];

    for (auto len = 1; len <= C; len++) {
        int end = C-len;
        for (auto l = 0; l <= end; l++) {
            int r = l+len-1, best = INF, lb = opt[l][r-1], rb = opt[l+1][r];
            if (l == r) { lb = 0; rb = C-1; }

            for (auto i = lb; i <= rb; i++) {
                int alt = A[l][i] + B[i][r];
                if (alt < best) {
                    best = alt;
                    opt[l][r] = i;
                }
            }
            res[l][r] = best;
        }
    }
    for (auto len = 1; len <= C; len++) {
        int end = len-1;
        for (auto r = C-1; r >= end; r--) {
            int l = r-len+1, best = INF, lb = opt[r-1][l], rb = opt[r][l+1];
            if (l == r) { lb = 0; rb = C-1; }

            for (auto i = lb; i <= rb; i++) {
                int alt = A[r][i] + B[i][l];
                if (alt < best) {
                    best = alt;
                    opt[r][l] = i;
                }
            }
            res[r][l] = best;
        }
    }
}
#define MID int mid = (l + r) / 2, lhs = i+1, rhs = i + (mid-l+1)*2;
void build(int i=1, int l=0, int r=(R-1)/BRUTE_TH) {
    assert(i < (MR*2/BRUTE_TH)+1);
    if (l == r) {
        brute(BRUTE_TH*l, min(BRUTE_TH*l+BRUTE_TH-1, R-1), seg[i]);
        return;
    }
    MID;
    build(lhs, l, mid); build(rhs, mid+1, r);
    comb(seg[lhs], seg[rhs], seg[i]);
}
void touch(int q, int i=1, int l=0, int r=(R-1)/BRUTE_TH) {
    assert(i < (MR*2/BRUTE_TH)+1);
    if (q > r || q < l) return;
    if (l == r) {
        brute(BRUTE_TH*l, min(BRUTE_TH*l+BRUTE_TH-1, R-1), seg[i]);
        return;
    }
    MID;
    touch(q, lhs, l, mid); touch(q, rhs, mid+1, r);
    comb(seg[lhs], seg[rhs], seg[i]);
}

// implement siggrader funs
void init(int R0, int C0, int H0[5000][200], int V0[5000][200]) {
    R = R0; C = C0;
    for (auto i = 0; i < R; i++)
        for (auto j = 0; j < C-1; j++)
            H[i][j] = H0[i][j];
    for (auto i = 0; i < R-1; i++)
        for (auto j = 0; j < C; j++)
            V[i][j] = V0[i][j];
    build();
}
void changeH(int P, int Q, int W) {
    H[P][Q] = W;
    touch(P/BRUTE_TH);
}
void changeV(int P, int Q, int W) {
    V[P][Q] = W;
    touch(P/BRUTE_TH);
}
int escape(int V1, int V2) { return seg[1][V1][V2]; }

#ifdef LOCAL
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int R, C; cin >> R >> C;
    int H0[5000][200], V0[5000][200];
    for (auto i = 0; i < R; i++)
        for (auto j = 0; j < C-1; j++)
            cin >> H0[i][j];
    for (auto i = 0; i < R-1; i++)
        for (auto j = 0; j < C; j++)
            cin >> V0[i][j];
    init(R, C, H0, V0);

    int Q; cin >> Q;
    while (Q--) {
        int T; cin >> T;
        if (T == 3) { 
            int a, b; cin >> a >> b;
            cout << escape(a, b) << '\n';
        }
        else {
            int p, q, w; cin >> p >> q >> w;
            if (T == 1) changeH(p, q, w);
            else changeV(p, q, w);
        }
    }

    return 0;
}
#endif