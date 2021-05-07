// ./ucc-coding-competition-21-p3-long-pizza.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 1e7 + 10;
int N, R, X, Y,
    psum[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> X >> Y >> R;
    while (R--) {
        int l, r; cin >> l >> r;
        psum[l]++; psum[r+1]--;
    }
    partial_sum(psum, psum+MN, psum);
    ll ans = 0;
    for (auto i = X; i <= Y; i++) ans += psum[i];
    cout << ans << '\n';

    return 0;
}