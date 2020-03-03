#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b, k;
    cin >> a >> b >> k;
    int mx = -INF;
    for (int i = 0; i <= k; i++) {
        mx = max(mx, a * i + b * (k - i));
    }
    cout << mx << endl;

    return 0;
}