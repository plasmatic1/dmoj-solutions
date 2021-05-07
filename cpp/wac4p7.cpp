// ./wesleys-anger-contest-4-problem-7-squirrel-cities.yml
// orz allen for showing me the light
// also why did u put the damage II pots in the ME system... >:(
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

using Change = tuple<int, int, int, int, int>;

const int MN = 1e5 + 1, MM = 3e5 + 1;
int N, M, Q,
    maxTime[MM], dur[MM], A[MM], B[MM], D[MM], T[MM];

int dsu[MN], sz[MN];
vector<Change> change;
void init() {
    fill(sz, sz+MN, 1);
    iota(dsu, dsu+MN, 0);
}
int rt(int x) { return x == dsu[x] ? x : rt(dsu[x]); }
int curId = 0;
void unite(int x, int y) {
    x = rt(x); y = rt(y);
    if (x == y) return;
    if (sz[x] < sz[y]) swap(x, y);

    change.emplace_back(y, dsu[y], x, sz[x], ++curId);
    dsu[y] = x;
    sz[x] += sz[y];
}
void undo(int to) {
    while (!change.empty()) {
        auto [y, dy, x, sx, id] = change.back();
        if (id < to) return;
        change.pop_back();
        dsu[y] = dy;
        sz[x] = sx;
    }
}
bool done() { return sz[rt(1)] == N; }

void solve(int l, int r, int tl, int tr, vector<int> es) {
    if (l > r) return;

    int mid = (l+r) / 2;

    int fstEdge = curId+1;
    for (auto i : es) {
        if (D[i] < dur[mid]) continue;

        if (rt(A[i]) != rt(B[i])) {
            unite(A[i], B[i]);
            if (done()) {
                maxTime[mid] = T[i];
                break;
            }
        }
    }
    if (!done()) maxTime[mid] = INF;
    undo(fstEdge);

    auto I = [&] (int dl, int dr, int tl, int tr, int d, int t) { return (dl <= d && d <= dr) || (tl <= t && t <= tr); };
    vector<int> lhs, rhs, extraLhs, extraRhs;
    for (auto i : es) {
        if (I(dur[l], dur[mid-1], tl, maxTime[mid], D[i], T[i]))
            lhs.push_back(i);
        if (I(dur[mid+1], dur[r], maxTime[mid], tr, D[i], T[i]))
            rhs.push_back(i);
        if (D[i] > dur[mid-1] && T[i] < tl)
            extraLhs.push_back(i);
        if (D[i] > dur[r] && T[i] < maxTime[mid])
            extraRhs.push_back(i);
    }

    fstEdge = curId+1;
    for (auto i : extraLhs)
        unite(A[i], B[i]);
    solve(l, mid-1, tl, maxTime[mid], lhs);
    undo(fstEdge);

    fstEdge = curId+1;
    for (auto i : extraRhs)
        unite(A[i], B[i]);
    solve(mid+1, r, maxTime[mid], tr, rhs);
    undo(fstEdge);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> Q;
    for (auto i = 0; i < M; i++) {
        cin >> A[i] >> B[i] >> D[i] >> T[i];
        dur[i] = D[i];
    }

    init();
    sort(dur, dur+M);
    int uniq = unique(dur, dur+M)-dur;
    vector<int> es(M); iota(es.begin(), es.end(), 0);
    sort(es.begin(), es.end(), [&] (const int a, const int b) { return T[a] < T[b]; });
    solve(0, uniq-1, 0, INF, es);

    while (Q--) {
        int d, t; cin >> d >> t;
        int nxt = lower_bound(dur, dur+uniq, d)-dur;
        if (nxt == uniq) cout << "NO\n";
        else cout << (maxTime[nxt] <= t ? "YES\n" : "NO\n");
    }

    return 0;
}