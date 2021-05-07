// ./ucc-coding-competition-21-p4-trampoline-jump.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 5e5 + 1, MOD = 2021;
int N,
    f[MN], dis[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    f[1] = 1; f[2] = 1;
    for (auto i = 3; i <= N; i++) f[i] = (f[i-1] + f[i-2]) % MOD;

    memset(dis, 0x3f, sizeof dis);
    queue<int> q; q.push(1); dis[1] = 0;
    while (!q.empty()) {
        int c = q.front(); q.pop();
        int a = f[c] + c%50;
        for (auto to : vector<int>{c-a, c+a, c-1, c+1}) {
            // printf("c=%d A=%d to=%d\n", c,a,to);
            if (1 <= to && to <= N && dis[to] == INF) {
                dis[to] = dis[c]+1;
                q.push(to);
            }
        }
    }
    cout << dis[N] << '\n';

    return 0;
}