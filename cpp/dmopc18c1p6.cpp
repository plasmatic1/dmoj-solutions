// ./dmopc-18-contest-1-p6-sorting.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

// MN=1002 for a very specific reason.  On the line: int alt = dp[p][l][j] + dp[p][j+1][r] + rq(i, 1, l, j) + rq(i, 0, j+1, r); note the expression "dp[p][j+1][r]".  Sometimes, j+1>N, which causes a very nasty bug when N=1000 exactly, causing the array to go out of bounds by referencing DP at 1001 and making the code fail on case 11 of the last batch.  I only accidentally fixed by setting N to 1011 out of curiosity/desperation, which is why I want to note the issue.  Setting it to 1002 fixes the problem (and similar issues in other places of the code) which is why N is exactly 1002 in this problem
const int MN = 1002, MB = 51;
int N, B,
    cnt[MB][2][MN], dp[2][MN][MN], opt[MN][MN];
string s[MN];

int rq(int b, bool q, int l, int r) { return cnt[b][q][r] - cnt[b][q][l-1]; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> B;
    {
        for (int i = 1; i <= N; i++) cin >> s[i];
        for (int i = 0; i < B; i++) {
            for (int j = 1; j <= N; j++) {
                cnt[i][0][j] = cnt[i][0][j-1] + (s[j][B-i-1] == '0');
                cnt[i][1][j] = cnt[i][1][j-1] + (s[j][B-i-1] == '1');
            }
        }
    }

    for (int i = 0; i < B; i++) {
        int c = i&1, p = !c;

        for (int len = 1; len <= N; len++) {
            int end = N-len+1;
            for (int l = 1; l <= end; l++) { int r = l+len-1;
                dp[c][l][r] = INF;
                int st = l-1, en = r;
                if (len > 1) {
                    st = opt[l][r-1];
                    en = opt[l+1][r];
                }

                for (int j = st; j <= en; j++) {
                    int alt = dp[p][l][j] + dp[p][j+1][r] + rq(i, 1, l, j) + rq(i, 0, j+1, r);
                    if (alt < dp[c][l][r]) {
                        opt[l][r] = j;
                        dp[c][l][r] = alt;
                    }
                }
            }
        }
    }

    cout << dp[(B-1)&1][1][N] << '\n';

    return 0;
}