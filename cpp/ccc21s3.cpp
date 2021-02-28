// s3.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

struct ps {
    int p, w, d;
    bool operator<(const ps &o) const {
        return p < o.p;
    }
};

const int MN = 2e5 + 1;
int N;
ps pss[MN];

ll calc(int k) {
    ll ans = 0;
    for (int i = 0; i < N; i++) {
        auto &p = pss[i];
        if (k > p.p + p.d) ans += ll(k - p.d - p.p) * p.w;
        else if (k < p.p - p.d) ans += ll(p.p - p.d - k) * p.w;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++) {
        int a, b, c; cin >> a >> b >> c;
        pss[i] = {a, b, c};
    }
    sort(pss, pss + N);

    ll l = -10, r = 1e9+10;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (calc(mid) >= calc(mid+1)) l = mid;
        else r = mid;
    }

    cout << min(calc(l), calc(l+1)) << '\n';;

    return 0;
}