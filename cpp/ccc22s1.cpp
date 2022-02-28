#include "bits/stdc++.h"
using namespace std;

using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int main() {
    int N; cin >> N;

    int ans = 0;
    for (int i = 0; i <= N; i++) {
        if (i*4 <= N)
            ans += (N - i*4) % 5 == 0;
    }

    cout << ans << '\n';

    return 0;
}