// ./tiles.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const ll MOD = 1e9 + 7;
ll fix(ll &&x) { x %= MOD; if (x < 0) x += MOD; return x; }
ll fix(ll &x) { x %= MOD; if (x < 0) x += MOD; return x; }
ll fpow(ll x, ll y, ll mod = MOD) {
    if (!y) return 1LL;
    return fpow(x * x % mod, y >> 1, mod) * ((y & 1) ? x : 1LL) % mod;
}
ll inv(ll x, ll mod = MOD) { return fpow(x, mod - 2, mod); }

const int MK = 51, M = 5, MSUB = 1<<M, MF = MK*2;
int N, K;
ll dp[MK][MK+1][MK][MSUB], invf[MF]; // number of non-empty rows, number of empty rows, number of black tiles, mask of prev. row
bool maskOk[MSUB];

ll C(int n, int k) {
    ll res = invf[k];
    for (auto i = 0; i < k; i++)
        res = res * (n-i) % MOD;
    return res;
}
ll SB(int boxes, int items) { return C(boxes+items-1, boxes-1); } // stars and bars

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // precompute INVF
    invf[MF-1] = 1;
    for (auto i = 1; i < MF; i++) invf[MF-1] = (invf[MF-1] * i) % MOD;
    invf[MF-1] = inv(invf[MF-1]);
    for (auto i = MF-2; i >= 0; i--) invf[i] = (invf[i+1] * (i+1)) % MOD;

    // precomp check if mask is 'ok'
    for (auto i = 0; i < MSUB; i++) {
        maskOk[i] = true;
        for (auto j = 0; j < M-1; j++)
            if (((i >> j) & 1) && ((i >> (j+1)) & 1))
                maskOk[i] = false;
    }

    cin >> N >> K;
    if (K == 0) return cout << "1\n", 0; // edge case

    // run DP
    dp[0][0][0][0] = 1LL;
    for (auto i = 0; i < MK; i++) {
        for (auto j = 0; j < MK+1; j++) {
            for (auto k = 0; k <= K; k++) {
                for (auto l = 0; l < MSUB; l++) {
                    // non-empty
                    for (auto m = 1; m < MSUB; m++) {
                        int cnt = __builtin_popcount(m);
                        if (maskOk[m] && i < MK-1 && k + cnt <= K && (l & m) == 0) {
                            ll &ret = dp[i+1][j][k+cnt][m];
                            ret = (ret + dp[i][j][k][l]) % MOD;
                        }
                    }
                    // empty
                    if (l != 0 && j < MK) {
                        ll &ret = dp[i][j+1][k][0];
                        ret = (ret + dp[i][j][k][l]) % MOD;
                    }
                }
            }
        }
    }

    // add the rest of the empty rows
    ll ans = 0;
    for (auto i = 0; i < MK; i++) {
        for (auto j = 0; j < MK+1; j++) {
            if (i+j <= N) {
                ll coeff = SB(j+2, N-i-j), cadd = 0; // empty rows are 'unordered'
                for (auto k = 1; k < MSUB; k++)
                    cadd += dp[i][j][K][k];
                ans = (ans + (cadd % MOD) * coeff) % MOD;
            }
        }
    }

    cout << ans << '\n';

    return 0;
}