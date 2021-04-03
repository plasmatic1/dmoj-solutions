// ./coci-10-contest-3-5-diferencija.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 3e5 + 1;
int N,
    A[MN];

ll run() {
    ll ans = 0, maxsum = 0;
    deque<int> dq{0};
    for (auto i = 1; i <= N; i++) {
        while (!dq.empty() && A[dq.back()] <= A[i]) {
            int b = dq.back(); dq.pop_back(); int bb = dq.back();
            maxsum -= ll(b - bb) * A[b];
        }
        maxsum += ll(i - dq.back()) * A[i];
        dq.push_back(i);
        ans += maxsum;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (auto i = 1; i <= N; i++)
        cin >> A[i];
    A[0] = INF;
    ll ans = run();
    for (auto i = 1; i <= N; i++)
        A[i] *= -1;
    ans += run();

    cout << ans << '\n';

    return 0;
}