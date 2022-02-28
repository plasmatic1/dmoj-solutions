#include "bits/stdc++.h"
using namespace std;

using P = pair<string, string>;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 1e6 + 10;
int N, M,
    A[MN];
ll K;

void die() {
    cout << "-1\n";
    exit(0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> K;

    if (K < N)
        die();

    K -= N;
    int ctr = 1;
    for (int i = N; i >= 1; i--) {
        ll take = min({K, (ll)M-1, (ll)N-i});
        if (i + take == N) {
            A[i] = ctr;
            ctr++;
        }
        else {
            A[i] = A[i + take + 1];
        }

        K -= take;
    }

    if (K > 0)
        die();

    for (int i = 1; i <= N; i++)
        cout << A[i] << " \n"[i == N];

    return 0;
}