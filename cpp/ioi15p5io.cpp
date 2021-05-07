// ./ioi-15-p5-sorting.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

const int MN = 2e5 + 1;
struct ChangeArray {
    vector<pii> A[MN];
    void change(int t, int x, int v) { A[x].emplace_back(t, v); }
    int get(int t, int x) { return (lower_bound(A[x].begin(), A[x].end(), pii{t+1, INT_MIN})-1)->second; }
};
ChangeArray per, idOf, chS;

int findSwapPairs(int N, int S0[], int M, int X[], int Y[], int P[], int Q[]) {
    // init
    int S[N]; copy(S0, S0+N, S);
    M = min(M, N); // we don't actually care about most values of M

    // setup per, idOf, and S
    for (auto i = 0; i < N; i++) {
        per.change(-1, i, i);
        idOf.change(-1, i, i);
        chS.change(-1, i, S[i]);
    }
    for (auto i = 0; i < M; i++) {
        // setup per/idOf
        per.change(i, X[i], per.get(i-1, Y[i]));
        per.change(i, Y[i], per.get(i-1, X[i]));
        idOf.change(i, per.get(i, X[i]), X[i]);
        idOf.change(i, per.get(i, Y[i]), Y[i]);
        // setup S
        swap(S[X[i]], S[Y[i]]);
        chS.change(i, X[i], S[X[i]]);
        chS.change(i, Y[i], S[Y[i]]);
    }
    auto trIdx = [&] (int x, int fromLev, int toLev) { // transform index from time fromLev to time toLev
        return idOf.get(toLev, per.get(fromLev, x));
    };

    // check if can do i+1 swaps
    auto check = [&] (int i) {
        vector<bool> vis(N);
        int need = N;
        for (auto j = 0; j < N; j++) {
            if (!vis[j]) {
                need--;
                for (auto c = j; !vis[c]; c = chS.get(i, c)) vis[c] = true;
            }
        }
        return need <= i+1;
    };

    // Binsearch for # swaps
    int l = -2, r = M-1;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid;
    }

    // Construct ans
    vector<bool> vis(N);
    vector<vector<int>> cycs;
    int need = N;
    for (auto j = 0; j < N; j++) {
        if (!vis[j]) {
            cycs.push_back(vector<int>());
            need--;
            for (auto c = j; !vis[c]; c = chS.get(r, c)) {
                vis[c] = true;
                cycs.back().push_back(c);
            }
        }
    }
    int curI = r-need+1;
    for (auto j = 0; j < curI; j++) P[j] = Q[j] = 0; // fill initial swaps with null swaps
    for (auto &cyc : cycs) { // sort array
        int sz = cyc.size();

        for (auto j = sz-1; j > 0; j--) {
            int a = cyc[j], b = cyc[j-1];
            P[curI] = trIdx(a, r, curI);
            Q[curI] = trIdx(b, r, curI);
            curI++;
        }
    }

    return r+1;
}

#define LOCAL
#ifdef LOCAL
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M; cin >> N;
    int S[N];
    for (auto i = 0; i < N; i++) cin >> S[i];
    cin >> M;
    int X[M], Y[M];
    for (auto i = 0; i < M; i++) cin >> X[i] >> Y[i];
    int P[M], Q[M]; memset(P, 0, sizeof P); memset(Q, 0, sizeof Q);

    int ans = findSwapPairs(N, S, M, X, Y, P, Q);
    cout << ans << '\n';
    for (auto i = 0; i < ans; i++) cout << P[i] << ' ' << Q[i] << '\n';
#ifndef ONLINE_JUDGE
    cout << "DEBUG\n";
    for (auto i = 0; i < ans; i++) {
        swap(S[X[i]], S[Y[i]]);
        swap(S[P[i]], S[Q[i]]);
    }
    cout << "final seq=";
    for (auto i = 0; i < N; i++) cout << S[i] << " \n"[i == N-1];
    for (auto i = 0; i < N; i++)
        if (S[i] != i)
            cout << "Wrong index " << i << " got " << S[i] << '\n';
#endif

    return 0;
}
#endif