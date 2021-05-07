// ./sac-21-p4-averaging-averages.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 1e6+1;
int N, Q,
    psum[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    for (auto i = 1; i <= N; i++)
        cin >> psum[i];
    partial_sum(psum, psum+MN, psum);
    while (Q--) {
        int l, r; cin >> l >> r;
        cout << (psum[r]-psum[l-1])/(r-l+1) << '\n';
    }

    return 0;
}