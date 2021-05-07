// ./ucc-coding-competition-21-p2-emerald-exchange.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 1e5 + 1;
int N,
    A[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (auto i = 0; i < N; i++)
        cin >> A[i];

    int ans = 0;
    for (auto i = 0; i < N; ) {
        if (A[i] % 2) i++;
        else {
            int j = i;
            while (j < N && A[j] % 2 == 0) j++;
            int cur = 0;
            for (auto k = i; k < j; k++) cur += A[k];
            ans = max(ans, cur);
            i = j;
        }
    }
    cout << ans << '\n';

    return 0;
}