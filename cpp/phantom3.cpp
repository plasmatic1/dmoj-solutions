#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 2e7 + 10, MNSQ = 1e5 + 1;
ll l, r;
bitset<MNSQ> isprime;
bitset<MN> isprime2;

ll ceilDiv(ll x, ll y) { return (x + y - 1) / y; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> l >> r;
    r--;

    // sieve
    isprime2.flip();
    isprime.flip();
    isprime[0] = isprime[1] = false;
    if (l == 1) // otherwise 0 and 1 are skipped
        isprime2[0] = false;
    for (int i = 2; i < MNSQ; i++) {
        if (isprime[i]) {
            for (int j = i * 2; j < MNSQ; j += i)
                isprime[j] = false;
            
            ll st = max(i * ceilDiv(l, i), (ll)i * 2);
            for (ll j = st; j <= r; j += i)
                isprime2[j - l] = false;
        }
    }

    // count
    int ans = 0;
    for (ll i = l; i <= r; i++)
        ans += isprime2[i - l];
    cout << ans << '\n';

    return 0;
}