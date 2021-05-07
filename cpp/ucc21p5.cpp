// ./ucc-coding-competition-21-p5-woodcutting-game.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 301;
int H1, W1, H2, W2,
    dp[3][MN][3][MN];

bool done(int h, int w) { return h == 1 && w == 1; }

int solve(int h1, int w1, int h2, int w2) { // 1->win
    if (done(h1, w1) && done(h2, w2)) return 0;
    int &ret = dp[h1][w1][h2][w2];
    if (ret != -1) return ret;

    ret = 0;
    // if (!done(h1, w1)) {
        if (h1 > 1) ret |= !solve(1, w1, 1, w1) || !solve(1, w1, h2, w2);
        for (auto i = 1; i < w1; i++) {
            ret |= !solve(h1, i, h1, w1-i);
            // ret |= !solve(h1, i, h2, w2);
            if (i <= 10)
                ret |= !solve(h2, w2, h1, w1-i);
        }
    // }
    // if (!done(h2, w2)) {
        if (h2 > 1) ret |= !solve(1, w2, 1, w2) || !solve(1, w2, h1, w1);
        for (auto i = 1; i < w2; i++) {
            ret |= !solve(h2, i, h2, w2-i);
            // ret |= !solve(h2, i, h1, w1);
            if (i <= 10)
                ret |= !solve(h1, w1, h2, w2-i);
        }
    // }

    // printf("dp %d %d %d %d v %d\n", h1,w1,h2,w2,ret);
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> H1 >> W1 >> H2 >> W2;
    memset(dp, -1, sizeof dp);
    int ans = solve(H1, W1, H2, W2);
    cout << "LW"[ans] << '\n';

    return 0;
}