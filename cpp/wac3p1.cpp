#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int t, d, p;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> t >> d >> p;
    int count = (t < -40) + (d >= 15) + (p > 50);
    cout << (count >= 2 ? "YES" : "NO") << '\n';

    return 0;
}