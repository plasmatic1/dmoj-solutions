// ./dmopc-20-contest-4-p1-missing-numbers.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T; cin >> T;
    while (T--) {
        ll N, S; cin >> N >> S;
        S = N*(N+1)/2 - S;
        ll l = max(1LL, S-N), r = (S-1)/2;
        // // ll mx = (S-1)/2;
        // ll mx = 0;
        // for (auto i = 1; i <= N; i++) {
        //     ll o = S-i;
        //     if (i < o)
        //         mx++;
        // }
        cout << max(0LL, r-l+1) << '\n';
    }

    return 0;
}