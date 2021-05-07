// ./coci-16-contest-1-6-vještica.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 16, MSUB = 1<<MN;
int N,
    fre[MN][26], dp[MSUB], common[MSUB][26];

int sumFre(int msk) {
    int sum = 0;
    for (auto i = 0; i < 26; i++) sum += common[msk][i];
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (auto i = 0; i < N; i++) {
        string s; cin >> s;
        for (auto c : s) fre[i][c - 'a']++;
    }

    int msub = 1<<N;
    for (auto i = 1; i < msub; i++) {
        memset(common[i], 0x3f, sizeof common[i]);
        for (auto j = 0; j < N; j++)
            if ((i >> j) & 1)
                for (auto k = 0; k < 26; k++) common[i][k] = min(common[i][k], fre[j][k]);
    }

    memset(dp, 0x3f, sizeof dp);
    dp[0] = 0;
    for (auto i = 1; i < msub; i++) {
        if (__builtin_popcount(i) == 1) dp[i] = sumFre(i);
        else {
            for (auto j = i; j; j = (j - 1) & i) {
                int s1 = j, s2 = i ^ j;
                if (s1 && s2) {
                    dp[i] = min(dp[i], dp[s1] + dp[s2] - sumFre(i));
                }
            }
        }
    }

    cout << dp[msub-1]+1 << '\n';

    return 0;
}