// ./coci-10-contest-4-6-hrpa.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int B = 5001;
ll N;
int dp[B][B];

// bool win(ll n, int pre) {
//     if (n == 0) return false;
//     int &ret = dp[n][pre];
//     if (ret != -1) return ret;
//     ret = 0;
//     for (auto i = 0; i <= min(2LL*pre, n); i++)
//         ret |= !win(n-i, i);
//     return ret;
// }
//
// int solve(int N) {
//     for (auto i = 1; i <= N; i++) {
//         if (!win(N-i, i))
//             return i;
//     }
//     return -1;
// }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    memset(dp, -1, sizeof dp);
    cin >> N;
    // cout << solve(N) << '\n';
    // for (auto i = 1; i <= N; i++) {
        // printf("i=%d S=%d\n", i, solve(i));
    // }

    set<ll, greater<ll>> fib;
    ll p1 = 0, p2 = 1;
    while (p1 + p2 <= N) {
        ll q = p1 + p2;
        fib.insert(q);
        p2 = p1;
        p1 = q;
    }

    ll ans = LLINF;
    for (auto &x : fib) {
        if (N >= x) {
            N %= x;
            ans = x;
        }
    }
    cout << ans << '\n';

    return 0;
}