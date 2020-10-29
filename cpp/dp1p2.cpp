#include <bits/stdc++.h>

using namespace std;

const int MN = 1001;
int N,
    A[MN], dp[MN][MN];

int main() {
    cin >> N;
    int tsum = 0;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        tsum += A[i];
        dp[i][i] = A[i];
    }
    for (int len = 2; len <= N; len++) {
        for (int l = 0; l < N - len + 1; l++) {
            int r = l + len - 1;
            dp[l][r] = max(A[l] - dp[l + 1][r], A[r] - dp[l][r - 1]);
        }
    }
    cout << ((dp[0][N - 1] + tsum) / 2) << '\n';
    return 0;
}