// ./ioi-14-p5-friend-standard-io.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 1e5 + 1;
int dp[MN][2]; // dp[i][not select/select] -> best ans when considering nodes j>i and that are connected to i, 

int findSample(int N, int C[], int H[], int P[]) {
    for (auto i = 0; i < N; i++) dp[i][1] = C[i];

    for (auto i = N-1; i > 0; i--) {
        int pre[2] = {dp[H[i]][0], dp[H[i]][1]};
        if (P[i] == 0) { // IAmYourFriend
            dp[H[i]][0] += max(dp[i][0], dp[i][1]);
            dp[H[i]][1] += dp[i][0];
        }
        else if (P[i] == 1) { // MyFriendsAreYourFriends
            dp[H[i]][0] += dp[i][0];
            dp[H[i]][1] = max({pre[1] + dp[i][1], pre[1] + dp[i][0], pre[0] + dp[i][1]});
        }
        else { // WeAreYourFriends
            dp[H[i]][0] += dp[i][0];
            dp[H[i]][1] = max({pre[1] + dp[i][0], pre[0] + dp[i][1]});
        }
    }

    return max(dp[0][0], dp[0][1]);
}

#define LOCAL
#ifdef LOCAL
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N; cin >> N;
    int C[N], H[N], P[N];
    for (auto i = 0; i < N; i++) {
        cin >> C[i];
    }
    for (auto i = 1; i < N; i++) {
        cin >> H[i] >> P[i];
    }

    cout << findSample(N, C, H, P) << '\n';

    return 0;
}
#endif