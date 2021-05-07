// ./an-animal-contest-1-p5-odd-alpacas.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 2e5 + 1;
int N,
    cnt[MN][2];
vector<pair<int, int>> g[MN];

void dfs(int c, int p, int dep) {
    cnt[c][dep&1]++;
    for (auto [to, w] : g[c]) {
        if (to != p) {
            dfs(to, c, dep+w);
            cnt[c][0] += cnt[to][0];
            cnt[c][1] += cnt[to][1];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (auto i = 0; i < N-1; i++) {
        int a, b, w; cin >> a >> b >> w;
        g[a].emplace_back(b, w&1);
        g[b].emplace_back(a, w&1);
    }
    dfs(1, -1, 0);
    auto compute = [&] (int a[2]) { ll paths = ll(a[0]) * a[1]; return abs(ll(N)*(N-1)/2-paths - paths); };
    ll ans = compute(cnt[1]);
    for (auto i = 2; i <= N; i++) {
        int cur[2]{cnt[1][0], cnt[1][1]};
        cur[0] += cnt[i][1] - cnt[i][0];
        cur[1] += cnt[i][0] - cnt[i][1];
        ans = min(ans, compute(cur));
    }
    cout << ans << '\n';

    return 0;
}