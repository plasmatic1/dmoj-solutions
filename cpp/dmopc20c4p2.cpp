// ./dmopc-20-contest-4-p2-beautiful-grids.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 3e5+1;
int K;
ll N, M,
   X[MN], Y[MN];
map<ll, int> rp, cp;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> K;
    for (auto i = 0; i < K; i++) {
        cin >> X[i] >> Y[i];
        rp[X[i]] ^= 1;
        cp[Y[i]] ^= 1;
    }
    int A = 0, B = 0;
    vector<ll> rs, cs;
    for (auto [r, p] : rp) {
        if (p) rs.push_back(r);
        A += p;
    }
    for (auto [c, p] : cp) {
        if (p) cs.push_back(c);
        B += p;
    }
    cout << max(A, B) << '\n';
    while (!rs.empty() && !cs.empty()) {
        cout << rs.back() << ' ' << cs.back() << '\n';
        rs.pop_back();
        cs.pop_back();
    }
    for (auto x : rs) cout << x << " 1\n";
    for (auto x : cs) cout << "1 " << x << '\n';

    return 0;
}