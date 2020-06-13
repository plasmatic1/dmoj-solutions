// whoops......

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

struct Ed {
    int a, b, c;
};

const int MN = 5e4 + 1, MM = 1e5 + 1, MK = 128; 
int N, M, Q;
Ed edges[MM];

// dsu garbage
int dsu[MK][MN];
int rt(int dsu[MN], int x) { return dsu[x] == x ? x : dsu[x] = rt(dsu, dsu[x]); }
void unite(int dsu[MN], int x, int y) { dsu[rt(dsu, x)] = rt(dsu, y); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> Q;
    for (int i = 0; i < M; i++) {
        auto &e = edges[i];
        cin >> e.a >> e.b >> e.c;
    }

    // MST
    for (int i = 0; i < MK; i++) {
        iota(dsu[i], dsu[i] + MN, 0);
        for (int j = 0; j < M; j++) {
            auto &e = edges[j];
            if ((i | e.c) == i)
                unite(dsu[i], e.a, e.b);
        }
    }

    while (Q--) {
        int a, b;
        cin >> a >> b;
        int ans = -1;
        for (int i = 0; i < MK; i++) {
            if (rt(dsu[i], a) == rt(dsu[i], b)) {
                ans = i;
                break;
            }
        }
        cout << ans << '\n';
    }

    return 0;
}