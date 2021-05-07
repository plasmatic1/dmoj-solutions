// ./sac-21-p5-friends-of-friends.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

struct DSU {
    vector<int> dsu;
    vector<int> sz;
    void init(int N) {
        dsu.resize(N + 1);
        iota(dsu.begin(), dsu.end(), 0);
        sz.assign(N+1, 1);
    }
    int rt(int x) { return dsu[x] == x ? x : dsu[x] = rt(dsu[x]); }
    void merge(int x, int y) { // x -> y
        x = rt(x); y = rt(y);
        if (x == y) return;
        dsu[y] = x;
        sz[x] += sz[y];
    }
    bool same(int x, int y) { return rt(x) == rt(y); }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, Q;
    cin >> N >> Q;
    DSU d; d.init(N);
    while (Q--) {
        int t; cin >> t;
        if (t == 1) {
            int a, b; cin >> a >> b;
            d.merge(a, b);
        }
        else {
            int a; cin >> a;
            cout << d.sz[d.rt(a)] << '\n';
        }
    }

    return 0;
}