// ./attraction.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 2e5 + 1;
int N, A, B,
    P[MN], C[MN][3];

void solve() {
    cin >> N >> A >> B;
    for (auto i = 0; i < A; i++)
        cin >> P[i];
    sort(P, P+A);

    {
        int lcnt = P[0]-1, rcnt = N-P[A-1];
        fill(C[0], C[0]+3, -INF);
        fill(C[A], C[A]+3, -INF);
        if (lcnt) C[0][0] = lcnt;
        if (rcnt) C[A][0] = rcnt;
    }
    for (auto i = 1; i < A; i++) {
        int cnt = P[i]-P[i-1]-1;
        if (cnt == 0) {
            C[i][0] = C[i][1] = C[i][2] = -INF;
            continue;
        }
        C[i][0] = (cnt+1) / 2;
        C[i][1] = cnt - cnt%2;
        C[i][2] = cnt;
        if (cnt == 1) C[i][1] = C[i][2] = -INF;
        if (cnt % 2 == 0) C[i][2] = -INF;
    }

    int ans = 0;
    vector<int> cnt(A+1);
    priority_queue<pair<int, int>> pq;
    for (auto i = 0; i <= A; i++)
        if (C[i][0] != -INF)
            pq.emplace(C[i][0], i);
    while (!pq.empty() && B > 0) {
        auto [gain, i] = pq.top(); pq.pop();
        ans += gain;

        if (cnt[i] < 2 && C[i][cnt[i]+1] != -INF)  {
            pq.emplace(C[i][cnt[i]+1] - C[i][cnt[i]], i);
        }
        cnt[i]++;
        B--;
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T; cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}