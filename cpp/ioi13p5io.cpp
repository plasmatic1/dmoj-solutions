// ./ioi-13-p5-robots.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

const int MN = 5e4 + 1, MT = 1e6 + 1;
int A, B, T,
    X[MN], Y[MN];
vector<pii> evt;

bool check(int mxt) {
    priority_queue<int> pq;
    for (auto [w, s] : evt) {
        if (s == INT_MIN) {
            for (auto i = 0; i < mxt && !pq.empty(); i++)
                pq.pop();
        }
        else
            pq.push(s);
    }

    for (auto i = B-1; i >= 0; i--) {
        for (auto j = 0; j < mxt && !pq.empty(); j++) {
            if (pq.top() >= Y[i])
                return false;
            pq.pop();
        }
    }

    return pq.empty();
}

int putaway(int A0, int B0, int T0, int X0[], int Y0[], int W0[], int S0[]) {
    A = A0; B = B0; T = T0;
    copy(X0, X0+A, X); copy(Y0, Y0+B, Y); 

    sort(X, X+A);
    sort(Y, Y+B);
    for (auto i = 0; i < T; i++) {
        int w = W0[i], s = S0[i];
        if (w >= X[A-1] && s >= Y[B-1])
            return -1;
        evt.emplace_back(w, s);
    }
    for (auto i = 0; i < A; i++)
        evt.emplace_back(X[i], INT_MIN);
    sort(evt.begin(), evt.end());

    int l = 0, r = T;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid;
    }
    return r;
}

#define LOCAL
#ifdef LOCAL
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b, t; cin >> a >> b >> t;
    int X[a], Y[b];
    for (auto i = 0; i < a; i++) cin >> X[i];
    for (auto i = 0; i < b; i++) cin >> Y[i];
    int W[t], S[t];
    for (auto i = 0; i < t; i++)
        cin >> W[i] >> S[i];
    cout << putaway(a, b, t, X, Y, W, S) << '\n';

    return 0;
}
#endif