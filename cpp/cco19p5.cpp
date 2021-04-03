// ./cco-19-p5-marshmallow-molecules.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 1e5 + 1;
int N, M;
set<int> g[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (auto i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        g[a].insert(b);
    }

    ll ans = 0;
    for (auto i = 1; i <= N; i++) {
        ans += g[i].size();
        if ((int)g[i].size() > 1) { // if it isn't..., we don't really care
            int st = *g[i].begin();
            g[i].erase(g[i].begin());
            if (g[i].size() > g[st].size()) swap(g[i], g[st]);
            for (auto x : g[i]) g[st].insert(x);
            g[i].clear();
        }
    }
    cout << ans << '\n';

    return 0;
}