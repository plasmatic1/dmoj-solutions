// ./uts-open-21-p3-latin-class.yml
// allen you naughty boy :)
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const ll MOD = 1e9 + 7;
const int MN = 1e5 + 1;
int N,
    H[MN];

ll fpow(ll x, ll y) {
    if (!y) return 1LL;
    return (fpow((x * x) % MOD, y >> 1) * ((y & 1) ? x : 1)) % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> H[i];

    ll ans = fpow(2, MOD-2), mx = 0, pre = 0;
    for (int i = 1; i <= N; i++) {
        if (H[i] >= mx) {
            mx = H[i];
            // printf("chmx i=%d v=%d pre=%lld cnt=%lld\n", i, H[i], pre, i-pre+1);
            ans = (ans * (i - pre + 1)) % MOD;
            pre = i;
        }
    }
    cout << ans << '\n';

    return 0;
}