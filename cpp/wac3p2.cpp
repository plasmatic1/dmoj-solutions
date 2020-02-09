#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MV = 1e6 + 1;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        int d;
        cin >> d;

        int third = d / 3;
        ll best = -LLINF;
        for (int i = third - 10; i <= third + 10; i++) {
            for (int j = third - 10; j <= third + 10; j++) {
                for (int k = third - 10; k <= third + 10; k++) {
                    if (i >= 0 && j >= 0 && k >= 0 && i + j + k == d)
                        best = max(best, (ll)i * j * k);
                }
            }
        }
        cout << best << '\n';
    }

    return 0;
}