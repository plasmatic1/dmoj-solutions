// ./quintessential-questions.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using T = tuple<int, int, int>;

const int MN = 2e5 + 1;
int N, M, K;
T best[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> K;
    for (auto i = 1; i <= K; i++) {
        int q, p, c; cin >> p >> q >> c;
        best[q] = max(best[q], T(c, -i, p));
    }
    for (auto i = 1; i <= N; i++) {
        auto [sc, idx, p] = best[i];
        // printf("i=%d sc=%d idx=%d p=%d\n", i,sc,idx,p);
        if (sc == 0) cout << "-1";
        else cout << p;
        cout << " \n"[i == N];
    }

    return 0;
}