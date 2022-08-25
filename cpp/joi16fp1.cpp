// ./joi-2017-final-p1----foehn-phenomena.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 2e5 + 10;
int N, Q;
ll S, T, D[MN];

ll dif(int k) {
    if (k < 1 || k > N) return 0;
    return D[k] > 0 ? S * -D[k] : T * -D[k];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q >> S >> T;
    ll pre = 0; cin >> pre;
    for (int i = 1; i <= N; i++) {
        ll x; cin >> x;
        D[i] = x - pre;
        pre = x;
    }

    ll d = 0;
    for (int i = 1; i <= N; i++) d += dif(i);

    while (Q--) {
        int l, r; ll x; cin >> l >> r >> x;
        d -= dif(l) + dif(r+1);
        D[l] += x;
        D[r+1] -= x;
        d += dif(l) + dif(r+1);
        cout << d << '\n';
    }

    return 0;
}