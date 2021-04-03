// ./coci-10-contest-5-5-dvoniz.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 1e5 + 1, LG = 18;
int N, maxpoint[MN];
ll S, psum[MN];


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> S;
    for (auto i = 1; i <= N; i++)
        cin >> psum[i];
    partial_sum(psum, psum+N+1, psum);

    for (auto i = 2; i <= N; i++) { // start point of SEQ2
        int l = 0, r = min(i-1, N-i+1)+1;
        while (l + 1 < r) {
            int mid = (l + r) / 2;
            if (psum[i+mid-1] - psum[i-1] <= S && psum[i-1] - psum[i-mid-1] <= S) l = mid;
            else r = mid;
        }
        maxpoint[i-l] = l;
    }

    int cmx = 0;
    for (auto i = 1; i <= N; i++) {
        cmx = max({0, cmx-1, maxpoint[i]});
        cout << 2*cmx << '\n';
    }

    return 0;
}