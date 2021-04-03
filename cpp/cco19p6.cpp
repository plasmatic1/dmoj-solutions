// ./cco-19-p6-bad-codes.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 51;
int N, M,
    dis[MN][MN][MN][MN]; // code #1, idx(code 1), code #2, idx(code 2)
string code[MN];

int len(int i) { return code[i].length(); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (auto i = 0; i < N; i++) {
        cin >> code[i];
    }

    using T = tuple<int, int, int, int>;
    queue<T> q;

    auto push = [&] (int a, int b, int c, int d, int w) {
        if (dis[a][b][c][d] == INF) {
            dis[a][b][c][d] = w;
            q.emplace(a, b, c, d);
        }
    };

    memset(dis, 0x3f, sizeof dis);
    for (auto i = 0; i < N; i++)
        for (auto j = i+1; j < N; j++)
            push(i, 0, j, 0, 0);
    while (!q.empty()) {
        auto [c1, i1, c2, i2] = q.front(); q.pop();
        int w = dis[c1][i1][c2][i2];
        if (i1 < len(c1) && i2 < len(c2) && code[c1][i1] == code[c2][i2])
            push(c1, i1+1, c2, i2+1, w+1);
        else if (i1 < len(c1) || i2 < len(c2)) {
            if (i1 == len(c1)) {
                for (auto i = 0; i < N; i++)
                    if (code[i][0] == code[c2][i2])
                        push(i, 1, c2, i2+1, w+1);
            }
            else if (i2 == len(c2)) {
                for (auto i = 0; i < N; i++)
                    if (code[i][0] == code[c1][i1])
                        push(c1, i1+1, i, 1, w+1);
            }
        }
    }

    int ans = INF;
    for (auto i = 0; i < N; i++)
        for (auto j = 0; j < N; j++)
            ans = min(ans, dis[i][len(i)][j][len(j)]);
    cout << (ans == INF ? -1 : ans) << '\n';

    return 0;
}