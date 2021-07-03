// ahahahaha I'm in p a i n :))))))))))

// ./apio-17-p2-travelling-merchant.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

/*
 * -dis*eff + profit > -inf
 * -dis*eff > -inf-profit
 * -dis > ceil((-inf-profit) / eff)
 */

const int MN = 101, MK = 1001;
int N, M, K,
    B[MN][MK], S[MN][MK];
ll dis[MN][MN];

ll dis2[MN][MN], maxProfit[MN][MN];
bool check(ll eff) {
    // build graph
    for (auto i = 1; i <= N; i++) {
        for (auto j = 1; j <= N; j++) {
            if (i != j) {
                ll prof = maxProfit[i][j];
                if (-dis[i][j] > (-LLINF-prof + eff-1) / eff)
                    dis2[i][j] = -dis[i][j]*eff + prof;
                else
                    dis2[i][j] = -LLINF;
            }
            else dis2[i][j] = -LLINF;
        }
    }

    // floyd-warshall again
    for (auto k = 1; k <= N; k++) 
        for (auto i = 1; i <= N; i++) 
            for (auto j = 1; j <= N; j++) 
                dis2[i][j] = max(dis2[i][j], dis2[i][k]+dis2[k][j]);
    // check
    for (auto i = 1; i <= N; i++) 
        if (dis2[i][i] >= 0)
            return true;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> K;
    for (auto i = 1; i <= N; i++) {
        for (auto j = 1; j <= K; j++)
            cin >> B[i][j] >> S[i][j];
    }

    memset(dis, 0x3f, sizeof dis);
    for (auto i = 1; i <= N; i++) 
        dis[i][i] = 0;
    for (auto i = 0; i < M; i++) {
        int a, b, w; cin >> a >> b >> w;
        dis[a][b] = min(dis[a][b], (ll)w);
    }
    for (auto k = 1; k <= N; k++) 
        for (auto i = 1; i <= N; i++) 
            for (auto j = 1; j <= N; j++) 
                dis[i][j] = min(dis[i][j], dis[i][k]+dis[k][j]);

    // precalc max profit
    for (auto i = 1; i <= K; i++) {
        for (auto j = 1; j <= N; j++) {
            for (auto k = 1; k <= N; k++) {
                if (B[j][i] != -1 && S[k][i] != -1)
                    maxProfit[j][k] = max(maxProfit[j][k], (ll)S[k][i]-B[j][i]);
            }
        }
    }

    // BS
    int l = 0, r = 1e9;
    while (l+1 < r) {
        int mid = (l+r) / 2;
        if (check(mid)) l = mid;
        else r = mid;
    }
    cout << l << '\n';

    return 0;
}