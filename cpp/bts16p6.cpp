// ./back-to-school-16-times-table.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 511;
int R, C, Q, sc, sr;
ll psum[MN][MN];

void dopsum() {
    for (auto i = 1; i < MN; i++)
        for (auto j = 1; j < MN; j++)
            psum[i][j] += psum[i-1][j] + psum[i][j-1] - psum[i-1][j-1];
}
void rangeinc(int x1, int y1, int x2, int y2, int q) {
    psum[x1][y1] += q;
    psum[x2+1][y1] -= q;
    psum[x1][y2+1] -= q;
    psum[x2+1][y2+1] += q;
}
pair<int, ll> dp[MN][MN];
pair<int, ll> dfs(int r, int c) {
    if (r <= 0 || r > R || c <= 0 || c > C) return {-INF, -LLINF};
    if (dp[r][c] != pair<int, ll>{0, 0}) return dp[r][c];
    for (pair<int, int> ADJ : initializer_list<pair<int, int>>{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}) {
        int rr = r + ADJ.first, cc = c + ADJ.second;
        if (rr <= 0 || rr > R || cc <= 0 || cc > C) continue;
        if (psum[rr][cc] > psum[r][c])
            dp[r][c] = max(dp[r][c], dfs(rr, cc));
    }
    dp[r][c].first++;
    dp[r][c].second += psum[r][c];
    return dp[r][c];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> C >> R >> Q;
    while (Q--) {
        int c, r, w, h, n; cin >> c >> r >> w >> h >> n;
        rangeinc(r, c, r+h-1, c+w-1, n);
        rangeinc(r, c+w, r+h-1, c+w, -n*w);
        rangeinc(r+h, c, r+h, c+w-1, -n*h);
        rangeinc(r+h, c+w, r+h, c+w, n*w*h);
    }
    dopsum(); dopsum();
    cin >> sc >> sr;
    dfs(sr, sc);
    cout << (dp[sr][sc].second % 1000000007) << '\n';

    return 0;
}