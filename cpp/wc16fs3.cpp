// ./wc-16-finals-s3-privacy.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 401;
int N, K,
    C[MN], cost[MN][MN], dp[MN][MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;
    K++;
    for (int i = 1; i <= N; i++) cin >> C[i];
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++)
            cost[i][j] = cost[i][j-1] + max(0, i - C[j]);
    }

    memset(dp, 0x3f, sizeof dp); dp[0][0] = 0;
    int ans = INF;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= K; j++) {
            for (int k = 0; k < i; k++) {
                int people = i-k-1;
                dp[i][j] = min(dp[i][j], dp[k][j-1] + cost[people][i] - cost[people][k]);
            }
            if (i == N) ans = min(ans, dp[i][j]);
        }
    }
    cout << ans << '\n';

    return 0;
}