// ./chris-candy.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int LIM = 1e5;
void die() { cout << "Sad Chris\n"; exit(0); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll K; cin >> K;
    K++;

    int ctr = 0;
    vector<int> pf;
    for (ll i = 2; i*i <= K; i++) {
        while (K % i == 0) {
            if ((int)pf.size() + i-1 > LIM) die();
            ctr++;
            for (auto j = 0; j < i-1; j++) pf.push_back(ctr);
            K /= i;
        }
    }
    if (K > 1) {
        if ((int)pf.size() + K-1 > LIM) die();
        ctr++;
        for (auto i = 0; i < K-1; i++) pf.push_back(ctr);
    }

    cout << pf.size() << '\n';
    int sz = pf.size();
    assert(sz <= LIM);
    for (auto i = 0; i < sz; i++) cout << pf[i] << " \n"[i == sz-1];

    return 0;
}