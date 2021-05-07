// ./ioi-16-p4-paint-by-numbers-standard-io.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 2e5 + 10, MK = 101;
int bpre[MN];
bool dp[MN][MK], rdp[MN][MK];

// check if ans is ok
int okpsum[MN];

string solve_puzzle(string s, int k, int c[]) {
    int n = s.length();

    // calculate DP
    auto runDP = [&] (bool dp[MN][MK]) {
        for (auto i = 0; i < n; i++) {
            bpre[i+1] = bpre[i] + (s[i] != '_');
        }
        dp[0][0] = true;
        for (auto i = 1; i <= n; i++) {
            for (auto j = 0; j <= k; j++) {
                if (j > 0) {
                    bool ok = true;
                    if (bpre[i] - bpre[i-c[j-1]] != c[j-1]) ok = false;
                    int pre = i-c[j-1];
                    if (j > 1) {
                        pre--;
                        if (s[pre] == 'X') ok = false;
                    }
                    if (pre < 0) ok = false;
                        
                    if (ok)
                        dp[i][j] |= dp[pre][j-1]; // black segment
                }
                if (s[i-1] != 'X') dp[i][j] |= dp[i-1][j]; // white square
            }
        }
    };
    runDP(dp);
    reverse(s.begin(), s.end());
    reverse(c, c+k);
    runDP(rdp);
    reverse(s.begin(), s.end());
    reverse(c, c+k);

    // get ans
    for (auto i = 0; i < n; i++) {
        bpre[i+1] = bpre[i] + (s[i] != '_');
    }
    for (auto i = 1; i <= n; i++) {
        for (auto j = 0; j < k; j++) {
            if (i >= c[j]) {
                bool ok = true;
                if (bpre[i] - bpre[i-c[j]] != c[j]) ok = false;
                int lpre = i-c[j], rpre = n-i;
                if (j > 0) {
                    lpre--;
                    if (s[lpre] == 'X') ok = false;
                }
                if (k-j-1 > 0) {
                    rpre--;
                    if (s[n-rpre-1] == 'X') ok = false;
                }
                if (!dp[lpre][j]) ok = false;
                if (!rdp[rpre][k-j-1]) ok = false;

                if (ok) {
                    okpsum[i-c[j]+1]++;
                    okpsum[i+1]--;
                }
            }
        }
    }
    partial_sum(okpsum, okpsum+MN, okpsum);

    // write ans
    string ans(n, '$');
    for (auto i = 0; i < n; i++) {
        bool okw = false; 
        for (auto j = 0; j <= k; j++) okw |= s[i] != 'X' && dp[i][j] && rdp[n-i-1][k-j];
        bool okb = okpsum[i+1] > 0;

        if (okw && okb) ans[i] = '?';
        else if (okw) ans[i] = '_';
        else if (okb) ans[i] = 'X';
        else assert(0);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s; cin >> s;
    int k; cin >> k;
    int c[k];
    for (auto i = 0; i < k; i++) cin >> c[i];

    cout << solve_puzzle(s, k, c) << '\n';

    return 0;
}