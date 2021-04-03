// ./jack-needs-help.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const ll MOD = 1e9 + 7;
const int MN = 2e5 + 1;
int N,
    A[MN], pfre[MN], lcmfre[MN];

vector<pair<int, int>> pf(int k) {
    vector<pair<int, int>> res;
    for (auto i = 2; i * i <= k; i++) {
        if (k % i == 0) {
            int cnt = 0;
            while (k % i == 0) {
                k /= i;
                cnt++;
            }
            res.emplace_back(i, cnt);
        }
    }
    if (k > 1) res.emplace_back(k, 1);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (auto i = 0; i < N; i++) {
        int x; cin >> x;
        for (auto p : pf(x)) {
            pfre[p.first] += p.second;
            lcmfre[p.first] = max(lcmfre[p.first], p.second);
        }
    }
    ll q = 1, p = 1;
    for (auto i = 1; i < MN; i++) {
        for (auto j = 0; j < pfre[i]-lcmfre[i]; j++)
            q = q * i % MOD;
    }
    cout << (p+q)%MOD << '\n';

    return 0;
}