// b.yml
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

const int MN = 1e5 + 1;
int N,
    X[MN], Y[MN];
vector<pii> pts;
map<int, vector<int>> xs, ys;

bool yup(int x, int y) {
    auto ptr = lower_bound(pts.begin(), pts.end(), pii(x, y));
    return ptr != pts.end() && ptr->first == x && ptr->second == y;
}

void solve() {
    for (auto i = 0; i < N; i++) {
        cin >> X[i] >> Y[i];
        pts.emplace_back(X[i], Y[i]);
        xs[Y[i]].push_back(X[i]);
        ys[X[i]].push_back(Y[i]);
    }
    sort(pts.begin(), pts.end());
    for (auto &p : xs) sort(p.second.begin(), p.second.end());
    for (auto &p : ys) sort(p.second.begin(), p.second.end());

    int ans = 0;
    for (auto i = 0; i < N; i++) {
        auto &vx = xs[Y[i]], &vy = ys[X[i]];

        if (vx.size() < vy.size()) {
            int j = lower_bound(vx.begin(), vx.end(), X[i]) - vx.begin(), sz = vx.size();
            for (; j < sz; j++) {
                int d = vx[j] - X[i];
                if (yup(X[i], Y[i]+d) && yup(X[i]+d, Y[i]+d))
                    ans = max(ans, d);
            }
        }
        else {
            int j = lower_bound(vy.begin(), vy.end(), Y[i]) - vy.begin(), sz = vy.size();
            for (; j < sz; j++) {
                int d = vy[j] - Y[i];
                if (yup(X[i]+d, Y[i]) && yup(X[i]+d, Y[i]+d))
                    ans = max(ans, d);
            }
        }
    }

    cout << (ans) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> N) {
        solve();
        pts.clear();
        xs.clear();
        ys.clear();
    }

    return 0;
}