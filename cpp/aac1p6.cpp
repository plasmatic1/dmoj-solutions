// ./an-animal-contest-1-p6-alpaca-distancing.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using T = tuple<int, bool, int>; // pos, is_query, idx

// template is 1-indexed
template <typename T> struct Ranks {
    vector<T> ranks;
    void init() {
        sort(ranks.begin(), ranks.end());
        ranks.resize(unique(ranks.begin(), ranks.end()) - ranks.begin());
    }
    template <typename It> void init(It st, It en) { ranks = vector<T>(st, en); init(); }
    void add(T v) { ranks.push_back(v); }
    int get(T v) { return lower_bound(ranks.begin(), ranks.end(), v) - ranks.begin() + 1; }
    int size() { return ranks.size(); }
};
// Template is 1-indexed (by default).  Can be made 0-indexed by modifying Comp
// Default: Point increment and prefix sum query
struct Comp {
    using Data = int;
    const Data vdef = 0;
    void applyUpdate(Data &to, Data &v) { to = max(to, v); }
    int transformInd(int idx, int N) { return idx; }
};
template <typename Comp> struct BIT {
    using Data = typename Comp::Data; Comp C;
    int N; vector<Data> bit;
    void init(int n0) {
        N = n0;
        bit.assign(N + 1, C.vdef);
    }
    void update(int x, Data v) {
        x = C.transformInd(x, N);
        for (; x <= N; x += x & -x)
            C.applyUpdate(bit[x], v);
    }
    Data query(int x) {
        x = C.transformInd(x, N);
        Data res = C.vdef;
        for (; x; x -= x & -x)
            C.applyUpdate(res, bit[x]);
        return res;
    }
};

const int MN = 1e5 + 1;
int N,
    dp[MN], B[MN], A[MN];
Ranks<int> r;
BIT<Comp> bit;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> N;
    vector<T> evt;
    for (auto i = 0; i < N; i++) {
        int a, b; cin >> a >> b;
        evt.emplace_back(a, true, i);
        evt.emplace_back(a+b, false, i);
        B[i] = b;
        A[i] = a;
        r.add(a);
        r.add(a-b);
    }
    A[N] = -INF;
    r.init();
    bit.init(r.size());
    sort(evt.begin(), evt.end());

    int ans = 0;
    deque<int> dq{N};
    for (auto [p, is_q, idx] : evt) {
        if (is_q) {
            dp[idx] = bit.query(r.get(A[idx]-B[idx])) + 1;
            ans = max(ans, dp[idx]);
        }
        else
            bit.update(r.get(A[idx]), dp[idx]);
    }
    cout << ans << '\n';

    return 0;
}