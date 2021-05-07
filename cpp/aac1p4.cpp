// ./an-animal-contest-1-p4-alpaca-arrays.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 1e6 + 1, MV = 1e5 + 1;
int N, Q,
    A[MN];
vector<int> ind[MV];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    for (auto i = 1; i <= N; i++) {
        cin >> A[i];
        ind[A[i]].push_back(i);
    }
    for (auto i = 1; i < MV; i++)
        ind[i].push_back(INF);
    auto nxt = [&] (int v, int i) {
        return *upper_bound(ind[v].begin(), ind[v].end(), i);
    };
    while (Q--) {
        int l, r, k; cin >> l >> r >> k;
        bool ok = false;
        for (auto i = 1; i*i <= k; i++) {
            if (k % i == 0 && i != k/i) {
                if (i >= MV || k/i >= MV) continue;
                int idx = nxt(i, l-1);
                if (idx < r && nxt(k/i, idx) <= r) {
                    ok = true;
                    break;
                }

                idx = nxt(k/i, l-1);
                if (idx < r && nxt(i, idx) <= r) {
                    ok = true;
                    break;
                }
            }
        }
        cout << (ok ? "YES\n" : "NO\n");
    }

    return 0;
}