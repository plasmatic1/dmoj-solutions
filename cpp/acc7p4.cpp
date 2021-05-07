// ./another-contest-7-problem-4-team-assignments.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const ll MOD = 998244353;
ll fix(ll &&x) { x %= MOD; if (x < 0) x += MOD; return x; }
ll fix(ll &x) { x %= MOD; if (x < 0) x += MOD; return x; }
ll fpow(ll x, ll y, ll mod = MOD) {
    if (!y) return 1LL;
    return fpow(x * x % mod, y >> 1, mod) * ((y & 1) ? x : 1LL) % mod;
}
ll inv(ll x, ll mod = MOD) { return fpow(x, mod - 2, mod); }
// N choose R
vector<ll> fact, invf;
void init_nchooser(int MN) {
    fact.resize(MN + 1); invf.resize(MN + 1);
    fact[0] = 1LL;
    for (int i = 1; i <= MN; i++) fact[i] = fix(fact[i - 1] * i);
    invf[MN] = inv(fact[MN]);
    for (auto i = MN-1; i >= 0; i--) invf[i] = fix(invf[i + 1] * (i + 1));
}
ll choose(ll N, ll K) { return fix(fact[N] * fix(invf[K] * invf[N - K])); }
ll permute(ll N, ll K) { return fix(fact[N] * invf[N - K]); }

const int MN = 1e5 + 1;
int K;
ll N;

ll solve(ll K) {
    ll ans = K * fpow(K-1, N-1) % MOD;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;
    init_nchooser(K);
    ll ans = 0;
    for (auto i = 0; i <= K; i++) {
        ll fc = solve(i) * choose(K, i) % MOD, mul = i % 2 == K % 2 ? 1 : -1;
        // ll fc = solve(i) % MOD, mul = i % 2 == K % 2 ? 1 : -1;
        // printf("i=%d fc=%lld mul=%lld\n",i,fc,mul);
        ans = (ans + mul * fc + MOD) % MOD;
    }
    cout << ans << '\n';

    return 0;
}