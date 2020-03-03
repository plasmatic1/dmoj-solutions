#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int mn = INF, mx = -INF;
    for (int i = 0; i < 4; i++) {
        int val;
        cin >> val;

        mn = min(mn, val);
        mx = max(mx, val);
    }

    cout << mn << '\n' << mx << '\n';

    return 0;
}