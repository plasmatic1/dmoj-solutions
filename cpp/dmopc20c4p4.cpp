// ./dmopc-20-contest-4-p4-javelin-throwing.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

/*

for all i
a_i+b_i = distinct(1..i)-1

*/

const int MN = 2e6+1;
int N,
    A[MN], distm[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    ll ans = 0;
    int cdistm = 0; // distinct-1
    deque<pii> q{pii(-1, INF)};
    for (auto i = 0; i < N; i++) {
        cin >> A[i];
        distm[i] = cdistm = max(cdistm, A[i]);
        ans += distm[i] - A[i];

        // same as brute forcing the distm updates... but we subtract i since we need to make an arith. seq. with d=1
        int bcost = distm[i] - i, pre = i;
        while (!q.empty() && q.back().second < bcost) {
            auto [tidx, tbcost] = q.back(); q.pop_back();
            ans += ll(pre - tidx) * (bcost - tbcost);
            pre = tidx;
        }
        q.emplace_back(i, bcost);

        cout << ans << " \n"[i == N-1];
    }

    return 0;
}