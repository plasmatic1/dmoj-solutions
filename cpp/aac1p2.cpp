// ./an-animal-contest-1-p2-alpaca-racing.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 1e6 + 1;
int N, K, X;
ll D, P;
priority_queue<ll> speed;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> D >> K >> X;
    for (auto i = 0; i < N; i++) {
        ll a; cin >> a;
        speed.push(a);
    }
    cin >> P;
    for (auto i = 0; i < K; i++) {
        auto tp = speed.top(); speed.pop();
        speed.push(tp * (100 - X) / 100);
    }

    cout << (speed.top() < P ? "YES" : "NO") << '\n';

    return 0;
}