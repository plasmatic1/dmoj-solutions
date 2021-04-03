// ./mec-16-p4-circuitry.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const string ANS[3] = {"not useful", "so so", "useful"};
const int MN = 501, MM = MN*MN;
int N, M,
    A[MM], B[MM], W[MM], ans[MM];
vector<tuple<int, int, int>> g[MN];

int dsu[MN];
int rt(int x) { return dsu[x] == x ? x : dsu[x] = rt(dsu[x]); }
void unite(int x, int y) { dsu[rt(y)] = rt(x); }

bool dfs(int c, int p, int wantWeight, int end, int ignore, vector<int> &ID) {
    if (c == end) return true;
    bool found = false;
    for (auto [to, w, i] : g[c]) {
        if (i == ignore) continue;
        if (to != p) {
            bool cfound = dfs(to, c, wantWeight, end, ignore, ID);
            if (cfound && w == wantWeight)
                ID.push_back(i);
            found |= cfound;
        }
    }
    return found;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    vector<tuple<int, int, int, int>> es;
    for (auto i = 0; i < M; i++) {
        cin >> A[i] >> B[i] >> W[i];
        es.emplace_back(W[i], i, A[i], B[i]);
    }
    sort(es.begin(), es.end());
    iota(dsu, dsu + MN, 0);
    for (auto [w, i, a, b] : es) {
        if (rt(a) != rt(b)) {
            unite(a, b);
            g[a].emplace_back(b, w, i);
            g[b].emplace_back(a, w, i);
            ans[i] = 2;
        }
    }
    for (auto i = 0; i < M; i++) {
        if (ans[i] != 2) {
            vector<int> f;
            dfs(A[i], -1, W[i], B[i], i, f);
            if (!f.empty()) {
                ans[i] = 1;
                for (int id : f) ans[id] = 1;
            }
        }
    }

    for (auto i = 0; i < M; i++)
        cout << ANS[ans[i]] << '\n';

    return 0;
}