// ./coci-17-contest-7-5-dostavljač.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 501;
int N, M,
    A[MN], dp[MN][MN][2]; // node (u), time, whether end at u or in subtree of u
vector<int> g[MN];

void dfs(int c, int p) {
    dp[c][1][0] = dp[c][1][1] = A[c];
    for (auto to : g[c]) {
        if (to != p) {
            dfs(to, c);
            int newv[MN][2]; memcpy(newv, dp[c], sizeof dp[c]);
            auto push = [&] (int a, int b, int v) {
                newv[a][b] = max(newv[a][b], v);
            };

            for (auto i = 0; i <= M; i++) {
                for (auto j = 0; j < 2; j++) {
                    for (auto k = 0; k <= M; k++) {
                        for (auto l = 0; l < 2; l++) {
                            int ni = i + k + 1 + (1 - l), nj = j + l;
                            if (ni <= M && nj < 2)
                                push(ni, nj, dp[c][i][j] + dp[to][k][l]);
                        }
                    }
                }
            }
            memcpy(dp[c], newv, sizeof newv);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (auto i = 0; i < N; i++) cin >> A[i];
    for (auto i = 0; i < N-1; i++) {
        int a, b; cin >> a >> b; a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(0, -1);
    int ans = 0;
    for (auto i = 0; i <= M; i++)
        for (auto j = 0; j < 2; j++)
            ans = max(ans, dp[0][i][j]);
    cout << ans << '\n';

    return 0;
}