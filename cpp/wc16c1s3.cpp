// ./wc-16-contest-1-s3-trickys-treats.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 1e5 + 1;
int N, M, T;
pair<int, int> hs[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> T;
    for (auto i = 0; i < N; i++)
        cin >> hs[i].first >> hs[i].second;
    sort(hs, hs+N);

    ll ans = 0, csum = 0;
    priority_queue<int, vector<int>, greater<int>> treat;
    for (auto i = 0; i < N; i++) {
        auto [p, c] = hs[i];
        treat.push(c); csum += c;
        while ((int)treat.size() > max(0, (M - 2*p) / T)) {
            csum -= treat.top();
            treat.pop();
        }
        ans = max(ans, csum);
    }
    cout << ans << '\n';

    return 0;
}