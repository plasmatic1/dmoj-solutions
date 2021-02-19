#pragma GCC optimize "Ofast"
// ./keen-keener.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

ll tri(ll k) { return k * (k-1) / 2; }

const int MN = 7001;
int N,
    A[MN];
ll pp[MN*(MN-1)/2];

// duplicate of (a, b)
// 4 possibilities
// a, b, a, b
// a, b, b, a
// b, a, a, b
// b, a, b, a
//
// (a, b, c) (b is counted twice)
// a==c but are different indices
//
// a, b, b, c
// a, b, c, b
// b, a, b, c
// b, a, c, b

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++) cin >> A[i];
    int ctr = 0;
    for (int i = 0; i < N; i++)
        for (int j = i+1; j < N; j++)
            pp[ctr++] = (ll)A[i] * A[j];
    sort(pp, pp + ctr);
    // count all "pairs"
    ll ans = 0;
    for (int i = 0; i < ctr; ) {
        int j = i;
        while (pp[i] == pp[j] && j < ctr) j++;
        ll c = j - i;
        // all
        ans += 4LL * c * c;

        i = j;
    }
    // pairs
    ans -= 4 * tri(N);
    // triples
    map<int, int> fre;
    for (int i = 0; i < N; i++) fre[A[i]]++;
    for (auto p : fre) {
        ll cc = p.second;
        ans -= 4 * (N-2) * cc * (cc - 1);
    }

    cout << ans << '\n';

    return 0;
}