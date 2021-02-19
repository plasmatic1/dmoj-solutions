// ./uts-open-21-p1-covid-party.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

ll f(ll k) {
    k++;
    return (k * k + 1) / 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll N; cin >> N;

    ll l = -1, r = 1e6;
    while (l + 1 < r) {
        ll mid = (l + r) / 2;
        if (f(mid) >= N) r = mid;
        else l = mid;
    }
    cout << r << '\n';

    return 0;
}