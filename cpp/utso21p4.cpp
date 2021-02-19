// ./uts-open-21-p4-lucky-graph.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;
#define pb push_back

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

const int MN = 2e5 + 10, MM = MN*2;
int N, M,
    A[MM], B[MM], deg[MN];
vector<pii> g[MN];
DSU d;

int sel[MM];
bool vis[MN];

int dfs2(int c, int p) {
    int parity = 0; 
    vis[c] = true;
    for (auto _to : g[c]) {
        int to = _to.first, id = _to.second;
        if (sel[id]) continue; // not tree edge

        if (to != p) {
            int top = dfs2(to, c);
            if (top == 0) {
                parity ^= 1;
            }
            else
                sel[id] = true;
        }
    }
    return parity;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        cin >> A[i] >> B[i];
        A[i]--; B[i]--;
        g[A[i]].emplace_back(B[i], i);
        g[B[i]].emplace_back(A[i], i);
    }
    d.init(N);

    for (int i = 0; i < M; i++) {
        if (!d.same(A[i], B[i])) {
            d.merge(A[i], B[i]);
        }
        else {
            sel[i] = true;
        }
    }
    for (int i = 0; i < N; i++) {
        if (!vis[i]) {
            dfs2(i, -1);
        }
    }

    int ans = 0;
    for (int i = 0; i < M; i++)
        if (!sel[i])
            deg[A[i]] ^= 1, deg[B[i]] ^= 1;
    for (int i = 0; i < N; i++)
        ans += deg[i];
    cout << ans << '\n';
    vector<int> es;
    for (int i = 0; i < M; i++)
        if (sel[i])
            es.pb(i+1);
    cout << es.size() << '\n';
    for (auto x : es) cout << (x) << ' ';
    cout << '\n';

    return 0;
}