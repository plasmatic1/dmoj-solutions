// ./dmopc-19-contest-7-p2-dinner-party.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

const int MN = 1e6 + 1;
int N,
    A[MN], asum[MN], B[MN], minv[2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (auto i = 0; i < N; i++) {
        cin >> A[i];
        if (i > 0) asum[i] = A[i] - asum[i-1];
        else asum[i] = A[i];
    }

    fill(minv, minv+2, INF);
    for (auto i = 0; i < N-1; i++) 
        minv[i & 1] = min(minv[i & 1], asum[i]);

    for (auto i = 0; i <= min(A[0], A[N-1]); i++) {
        int min0 = minv[0], min1 = minv[1], lastTo = (N-1) & 1, endSum = 0;
        if (lastTo) {
            min1 = min(min1, asum[N-1]);
            endSum = asum[N-1];
        }
        else {
            min0 = min(min0, asum[N-1] - 2*i);
            endSum = asum[N-1] - 2*i;
        }

        if (min0 >= 0 && min1 >= 0 && endSum == 0) {
            A[0] -= i; A[N-1] -= i;
            vector<pii> ops;
            for (auto j = 0; j < N-1; j++) {
                while (A[j] > 0) {
                    A[j]--;
                    A[j+1]--;
                    ops.emplace_back(j, j+1);
                }
            }
            cout << "YES\n" << ops.size()+i << '\n';
            for (auto j = 0; j < i; j++) cout << "0 " << N-1 << '\n';
            for (auto [a, b] : ops) cout << a << ' ' << b << '\n';
            return 0;
        }

        minv[0]--;
        minv[1]++;
    }

    cout << "NO\n";

    return 0;
}