// ./cco-preparation-test-2-subsets.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

inline int kth(int msk, int k) { return (msk >> k) & 1; }

const ll MOD = 1e9 + 1;
const int MN = 1e5 + 1;
int N;

const int MP = 18, MP2 = 17, MSUB = 1<<MP2;
ll dp[2][MSUB];
ll solve(int n) { // solve for a single base value
    vector<int> rowLen;
    for (auto i = 0, p2 = 1; p2 <= n; i++, p2 *= 2) {
        int p3 = 1, mp3 = 0;
        for (; p2*p3*3 <= n; p3 *= 3, mp3++);
        rowLen.push_back(mp3+1);
    }

    int r = rowLen.size(), msub = 1<<rowLen[0];
    auto cdp = dp[0], ndp = dp[1];
    auto push = [&] (int j, ll v) { ndp[j] = (ndp[j] + v) % MOD; };

    fill(cdp, cdp+msub, 0); cdp[0] = cdp[1] = 1;
    for (auto i = 0; i < r; i++) {
        int c = rowLen[i];
        for (auto j = 0; j < c; j++) {
            fill(ndp, ndp+msub, 0);

            for (auto msk = 0; msk < msub; msk++) {
                if (!cdp[msk]) continue;

                int nmskBase = (msk << 1) & (msub-1);
                // no take
                push(nmskBase, cdp[msk]);
                // yes take
                if (j != c-1) { // not end of row
                    if (!kth(msk, 0) && (i == 0 || !kth(msk, rowLen[i-1]-1)))
                        push(nmskBase | 1, cdp[msk]);
                }
                else { // end of row
                    if (!kth(msk, rowLen[i]-1))
                        push(nmskBase | 1, cdp[msk]);
                }
            }

            swap(cdp, ndp);
        }
    }

    ll res = 0;
    for (auto k = 0; k < msub; k++) res = (res + ndp[k]) % MOD;
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    ll ans = 1;
    for (auto i = 1; i <= N; i++)
        if (i % 2 && i % 3)
            ans = ans * solve(N/i) % MOD;

    cout << ans << '\n';

    return 0;
}