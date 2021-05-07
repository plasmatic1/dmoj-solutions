// ./dmopc-20-contest-5-p2-on-the-clock.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

/*
 * y=(R/C)x
 * y < Rx/C
 * Cy < Rx
 *
 * Same w/ >
 */

const int MN = 1e6 + 1;
int R, C;

bool under(int y, int x) { return ll(C) * y < ll(R) * x; }
bool over(int y, int x) { return ll(C) * y > ll(R) * x; }

bool inside(int y, int x) {
    // printf("inside x=%d y=%d\n",x,y);
    return over(y, x-1) && under(y-1, x);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> R >> C;
    vector<pii> ans;

    int l = 1, r = 0;
    for (auto i = 1; i <= R; i++) {
        while (r < C && inside(i, r+1)) r++;
        while (l <= r && !inside(i, l)) l++;
        // printf("i=%d l=%d r=%d\n", i,l,r);

        for (auto j = l; j <= r; j++) ans.emplace_back(i, j);
    }

    cout << ans.size() << '\n';
    sort(ans.begin(), ans.end());
    for (auto [x, y] : ans) cout << x << ' ' << y << '\n';

    return 0;
}