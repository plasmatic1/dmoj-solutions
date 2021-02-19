// ./clumsy-cindy.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 5001;
int N,
    A[MN], B[MN], C[MN], dp[MN][MN];

void runSMin(int i) {
    for (int j = MN-2; j >= 0; j--)
        dp[i][j] = min(dp[i][j], dp[i][j+1]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> C[i];
    for (int i = 1; i <= N; i++) cin >> A[i] >> B[i];
    memset(dp, 0x3f, sizeof dp);
    int ans = INF;
    for (int i = 0; i < MN; i++) {
        if (i * A[1] >= C[1])
            dp[1][i] = i;
        if (N == 1) ans = min(ans, dp[1][i]);
    }
    runSMin(1);
    for (int i = 2; i <= N; i++) {
        int ptr = MN;
        for (int j = 0; j < MN; j++) {
            while (ptr > 0 && (ptr-1) * B[i-1] + j * A[i] >= C[i]) ptr--;

            if (ptr < MN) dp[i][j] = dp[i-1][ptr] + j;
            if (i == N) ans = min(ans, dp[i][j]);
        }
        runSMin(i);
    }
    cout << ans << '\n';

    return 0;
}