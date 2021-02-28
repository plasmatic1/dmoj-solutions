// s2.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 5e6+1;
int N, M, Q;
bool pr[MN], pc[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> Q;
    while (Q--) {
        char t; int x; cin >> t >> x;
        if (t == 'R') pr[x] ^= 1;
        else if (t == 'C') pc[x] ^= 1;
    }
    int ans = 0;
    for (auto i = 1; i <= N; i++)
        for (auto j = 1; j <= M; j++)
            ans += pr[i] ^ pc[j];
    cout << ans << '\n';

    return 0;
}