// ./wc-16-contest-4-s3-night-howlers.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

const int MN = 2e5 + 1;
int N, K,
    alpha[MN];
pii wolf[MN];

int bit[MN];
void add(int x, int v) {
    for (; x <= N; x += x & -x) bit[x] += v;
}
int query(int x) {
    int sum = 0;
    for (; x; x -= x & -x) sum += bit[x];
    return sum;
}

// get range
pii qrange(int k, int R) {
    int r = upper_bound(wolf, wolf+N, pii{wolf[k].first + R, INF}) - 1 - wolf;
    int l = lower_bound(wolf, wolf+N, pii{wolf[k].first - R, -1}) - wolf;
    return {l, r};
}

int check(int R) {
    fill(bit, bit + N + 1, 0);
    int res = 0;
    for (int i = 0; i < N; i++) {
        int q = alpha[i];
        if (query(q+1) <= 0) res++;
        auto range = qrange(q, R);
        add(range.first+1, 1);
        add(range.second+2, -1);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;
    for (int i = 0; i < N; i++) cin >> wolf[i].first >> wolf[i].second;
    sort(wolf, wolf + N);
    iota(alpha, alpha + N, 0);
    sort(alpha, alpha + N, [&] (const int a, const int b) { return wolf[a].second < wolf[b].second; });

    int l = 0, r = 1e9;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (check(mid) > K) l = mid;
        else r = mid; // r is ans
    }
    cout << r << '\n';

    return 0;
}