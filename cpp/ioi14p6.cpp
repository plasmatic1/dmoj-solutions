// ./ioi-14-p6-holiday-standard-io.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 1e5 + 1, MOVE = 3;

int SZ;
vector<int> rnk;
int get(int k) { return lower_bound(rnk.begin(), rnk.end(), k) - rnk.begin() + 1; }

int cbit[MN];
ll sbit[MN];
void reset() {
    memset(cbit, 0, sizeof cbit);
    memset(sbit, 0, sizeof sbit);
}
void upd(int x) {
    int v = x; x = get(abs(x));
    for (; x < MN; x += x & -x) {
        cbit[x] += (v > 0) - (v < 0);
        sbit[x] += v;
    }
}
int qcnt(int x) { int sum = 0;
    for (; x; x -= x & -x)
        sum += cbit[x];
    return sum;
}
ll qsum(int x) { ll sum = 0;
    for (; x; x -= x & -x)
        sum += sbit[x];
    return sum;
}
ll firstk(int k) {
    int idx = 0, cnt = 0;
    for (auto bit = 65536; bit; bit >>= 1) {
        int alt = idx | bit;
        if (alt < MN && cnt + cbit[alt] < k) {
            cnt += cbit[alt];
            idx = alt;
        }
    }
    return qsum(idx+1) - ll(qcnt(idx+1) - k) * rnk[idx];
}
ll topk(int k) {
    return qsum(MN-1) - firstk(qcnt(MN-1)-k);
}

long long int _findMaxAttraction(int N, int S, int D, int A[]) {
    reset();
    ll ans = 0;

    ll pre = -1;
    int opt = -1, ptr = S-1;
    auto move = [&] (int to) { 
        while (ptr < to) upd(A[++ptr]);
        while (ptr > to) upd(-A[ptr--]);
    };
    auto query = [&] (int leftBound, int idx) {
        int trav = 2*(S-leftBound) + idx-S, left = D-trav;
        if (left <= 0) return 0LL;
        move(idx);
        return topk(min(left, qcnt(MN-1)));
    };
    auto checkOpt = [&] (int leftBound, int idx) {
        ll alt = query(leftBound, idx);
        if (alt > pre) {
            opt = idx;
            pre = alt;
        }
    };

    for (auto i = S; i >= 0; i--) {
        if (i < S)
            upd(A[i]);

        if (i == S)
            for (auto j = S; j < N; j++)
                checkOpt(i, j);
        else {
            pre = query(i, opt); // have to update the curr ans with the new value at opt
            if (opt > S)
                checkOpt(i, opt-1);
        }
        ans = max(ans, pre);
    }

    return ans;
}

long long int findMaxAttraction(int n, int start, int d, int attraction[]) {
    // do rnk compress
    for (auto i = 0; i < n; i++)
        rnk.push_back(attraction[i]);
    sort(rnk.begin(), rnk.end());
    rnk.resize(unique(rnk.begin(), rnk.end()) - rnk.begin());
    SZ = rnk.size();

    ll ans = _findMaxAttraction(n, start, d, attraction);
    reverse(attraction, attraction+n);
    if (start != 0)
        ans = max(ans, _findMaxAttraction(n, n-start-1, d, attraction));
    return ans;
}

#ifdef LOCAL
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, S, D; cin >> N >> S >> D;
    int A[N];
    for (auto i = 0; i < N; i++)
        cin >> A[i];
    cout << findMaxAttraction(N, S, D, A) << '\n';

    return 0;
}
#endif