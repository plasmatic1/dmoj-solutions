// ./dmopc-20-contest-4-p3-roving-roombas.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

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
    void applyUpdate(Data &to, Data &v) { to += v; }
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

const int MN = 2e5 + 1;
int N, M,
    X[MN];
vector<tuple<int, int, int>> evt; // 0->roomba, 1->cord
Ranks<int> rs;
BIT<Comp> bit;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (auto i = 0; i < N; i++) {
        int x, y; cin >> x >> y;
        evt.emplace_back(y, 0, x);
        rs.add(x);
    }
    for (auto i = 0; i < M; i++) {
        int x, y; cin >> x >> y;
        evt.emplace_back(y, 1, x);
        X[i] = x;
        rs.add(x);
    }
    rs.init();
    bit.init(rs.size());
    sort(evt.begin(), evt.end());
    ll ans = 0;
    for (auto i = 0; i < M; i++)
        bit.update(rs.get(X[i]), 1);
    for (auto [y, t, x] : evt) {
        if (t == 1) {
            bit.update(rs.get(x), -1);
        }
        else {
            ans += bit.query(rs.get(x));
        }
    }
    cout << ans << '\n';

    return 0;
}