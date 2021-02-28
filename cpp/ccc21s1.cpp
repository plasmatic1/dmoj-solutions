// s1.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 10002;
int N, 
    H[MN], W[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (auto i = 1; i <= N+1; i++)
        cin >> H[i];
    for (auto i = 1; i <= N; i++)
        cin >> W[i];

    int ans = 0;
    for (auto i = 1; i <= N; i++) {
        int rect = min(H[i], H[i+1]) * W[i] * 2;
        int tri = abs(H[i+1] - H[i]) * W[i];
        ans += rect;
        ans += tri;
    }

    if (ans % 2 == 0) cout << (ans/2) << '\n';
    else {
        cout << (ans/2) << ".5\n";
    }

    return 0;
}