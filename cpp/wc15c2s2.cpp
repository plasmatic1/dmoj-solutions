// ./wc-15-contest-2-s2-attack-of-the-clones.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

// if odd, influence min of prev. row, max of nxt. row
// if even, influence max of prev. row, min of nxt. row

const int MN = 2e5 + 1, MX = 40001;
int N;

ll get(int a, int b, int c, int d) {
    b = abs(b);
    d = abs(d);
    return abs(c - a) + abs(d - b);
}

bool ok(pii p) {
    return p != pii{-1, -1} && p != pii{MX, MX};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    ll ans = 0;
    set<pii> ps;
    ps.insert({-1, -1});
    ps.insert({1, 1});
    ps.insert({MX, MX});

    for (int i = 0; i < N; i++) {
        int r, c; cin >> r >> c;

        pii p{r, c};
        if (r % 2 == 0) p.second *= -1; // sort other way

        auto nxt = ps.lower_bound(p), pre = nxt; pre--;
        if (ok(*nxt) && ok(*pre)) {
            ans -= get(pre->first, pre->second, nxt->first, nxt->second);
        }
        if (ok(*nxt)) {
            ans += get(p.first, p.second, nxt->first, nxt->second);
        }
        if (ok(*pre)) {
            ans += get(pre->first, pre->second, p.first, p.second);
        }
        ps.insert(p);

        cout << ans << '\n';
    }

    return 0;
}