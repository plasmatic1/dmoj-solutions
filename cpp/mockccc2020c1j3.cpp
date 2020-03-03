#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long double w, h;
    cin >> w >> h;
    cout << fixed << setprecision(2) << (w * h / 4.) << endl;

    return 0;
}