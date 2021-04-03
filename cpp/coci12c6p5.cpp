// ./coci-12-contest-6-5-jedan.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const ll MOD = 1e9+7;
const int MN = 1e4+1;
int N;
ll dp[2][MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    int fst; cin >> fst;
    if (fst != 0 && fst != -1) {
        cout << "0\n";
        return 0;
    }

    ll *dp0 = dp[0], *dp1 = dp[1]; // stupid memory limit...
    dp0[0] = 1;
    for (auto i = 0; i < N-1; i++) {
        int h; cin >> h;
        fill(dp1, dp1+MN, 0);

        for (auto j = 0; j < MN; j++) {
            if (j > 0) dp1[j-1] += dp0[j];
            if (j < MN-1) dp1[j+1] += dp0[j];
            dp1[j] += dp0[j];
        }
        for (auto j = 0; j < MN; j++) {
            if (h != -1 && j != h)
                dp1[j] = 0;
            dp1[j] %= MOD;
        }

        swap(dp0, dp1);
    }
    cout << dp0[0] << '\n';

    return 0;
}