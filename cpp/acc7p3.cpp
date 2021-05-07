// ./another-contest-7-problem-3-network-connections.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

struct DSU {
    vector<int> dsu;
    void init(int N) {
        dsu.resize(N + 1);
        iota(dsu.begin(), dsu.end(), 0);
    }
    int rt(int x) { return dsu[x] == x ? x : dsu[x] = rt(dsu[x]); }
    void merge(int x, int y) { // x -> y
        dsu[rt(x)] = rt(y); }
    bool same(int x, int y) { return rt(x) == rt(y); }
};

using T = tuple<int, int, int>;
const int MN = 1e5 + 1;
int N, M;
pair<int, int> fs[MN];
vector<T> edges;
DSU dsu;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (auto i = 1; i <= N; i++) {
        cin >> fs[i].first;
        fs[i].second = i;
    }
    sort(fs+1, fs+N+1);
    for (auto i = 1; i < N; i++)
        edges.emplace_back(fs[i+1].first - fs[i].first, fs[i].second, fs[i+1].second);
    sort(edges.begin(), edges.end());
    dsu.init(N);
    for (auto i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        dsu.merge(a, b);
    }
    ll ans = 0;
    for (auto [w, a, b] : edges) {
        if (!dsu.same(a, b)) {
            dsu.merge(a, b);
            ans += w;
        }
    }
    cout << ans << '\n';

    return 0;
}