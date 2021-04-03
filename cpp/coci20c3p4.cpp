// ./coci-20-contest-3-4-selotejp.yml
#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt"
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

string __(int k) {
    return bitset<4>(k).to_string();
}
#define _(k) (__(k).c_str())

const int MN = 1011, MM = 11, MSUB = 1 << 10;
int N, M,
    msk[MN], dp[MN][MSUB], segc[MSUB];
string grid[MN];

int getbit(int msk, int k) {
    return (msk >> k) & 1;
}

int hcost(int from, int to) {
    return __builtin_popcount((from | to) ^ from);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    int msub = 1 << M;
    for (auto i = 0; i < N; i++) {
        cin >> grid[i];
        for (auto j = 0; j < M; j++)
            msk[i] += (1 << j) * (grid[i][j] == '#');
    }

    for (auto i = 0; i < msub; i++) {
        int pre = 0;
        for (auto j = 0; j < M; j++) {
            if (((i >> j) & 1) && pre == 0)
                segc[i]++;
            pre = (i >> j) & 1;
        }
    }

    memset(dp, 0x3f, sizeof dp);
    dp[0][0] = 0;
    for (auto i = 0; i < N; i++) {
        for (auto j = 0; j < msub; j++) {
            if (dp[i][j] == INF) continue;
            for (auto k = 0; k < msub; k++) {
                if ((msk[i] | k) == msk[i]) { // can only take bits part of msk[i]
                    int nmsk = msk[i] ^ k, &ret = dp[i+1][nmsk];
                    ret = min(ret, dp[i][j] + hcost(j, nmsk) + segc[k]);
                }
            }
        }
    }

    int ans = INF;
    for (auto i = 0; i < msub; i++) ans = min(ans, dp[N][i]);
    cout << ans << '\n';

    return 0;
}