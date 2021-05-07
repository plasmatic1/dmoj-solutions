// ./coci-16-contest-5-4-ronald.yml
// dame da ne more like da ne d a n  e a m i r i t e h o m i e s
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 1001;
int N, M,
    adj[MN][MN], clr[MN];
void dfs(int c, int cclr) {
    if (clr[c] != -1) {
        if (cclr != clr[c]) {
            cout << "NE\n";
            exit(0);
        }
        return;
    }
    clr[c] = cclr;
    for (auto i = 0; i < N; i++)
        if (i != c)
            dfs(i, cclr ^ 1 ^ adj[c][i]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (auto i = 0; i < M; i++) {
        int a, b; cin >> a >> b; a--; b--;
        adj[a][b] = adj[b][a] = 1;
    }
    memset(clr, -1, sizeof clr);
    dfs(1, 0);
    cout << "DA\n";

    return 0;
}