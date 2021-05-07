// ./dmopc-20-contest-5-p3-bottom-row.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

inline bool I(int a, int b, int c, int d) { return max(a, c) <= min(b, d); }
inline bool I(pii &a, pii &b) { return I(a.first, a.second, b.first, b.second); }

const int MN = 1e6 + 1;
int N, K,
    bcol[MN];
vector<pii> seg[MN];

int dp[MN][2];
pii par[MN][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> N >> K;
    for (auto i = 1; i <= N; i++) bcol[i] = N+1;
    for (auto i = 0; i < K; i++) {
        int r, c; cin >> r >> c;
        bcol[r] = c;
    }

    for (auto i = 1; i <= N; i++) {
        seg[i].emplace_back(1, bcol[i]-1);
        seg[i].emplace_back(bcol[i]+1, N);
    }

    int st = N > bcol[N];
    dp[N][st] = N; par[N][st] = {N+1, 0};
    for (auto i = N-1; i >= 1; i--) {
        for (auto j = 0; j < 2; j++) {
            for (auto k = 1; k >= 0; k--) { // take rightmost
                // auto [aa,bb]=seg[i][j];
                // auto [cc,dd]=seg[i+1][k];
                // printf("i=%d j=%d test k=%d, segj=%d,%d segk=%d,%d dpk=%d OK1=%d\n", i,j,k,aa,bb,cc,dd,dp[i+1][k],I(aa,bb,cc,dd));
                if (I(seg[i][j], seg[i+1][k]) && dp[i+1][k] >= seg[i][j].first) {
                    int alt = min(dp[i+1][k], seg[i][j].second);
                    if (alt > dp[i][j]) {
                        dp[i][j] = alt;
                        par[i][j] = {i+1, k};
                    }
                }
            }
        }
        // printf("i=%d BLOCK=%d dp=%d,%d\n", i,bcol[i],dp[i][0],dp[i][1]);
    }

    if (dp[1][0] == 0) cout << "IMPOSSIBLE\n";
    else {
        int r = 1, c = 0, curCol = 1;
        // int its=10;
        while (r <= N) {
            while (curCol < dp[r][c]) {
                cout << 'R';
                curCol++;
            }
            if (r < N) cout << 'U';

            // printf("r=%d c=%d curCol=

            auto [pr, pc] = par[r][c];
            r = pr;
            c = pc;
        }

        cout << '\n';
    }

    return 0;
}