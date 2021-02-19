// ./uts-open-21-p2-prime-array.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int ari(int k) { return k * (k+1) / 2; }

const int MN = 101;
int K,
    val[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> K;

    for (int i = 1; i < MN; i++) {
        int ck = ari(i) - K;
        if (ck < 0) continue;
        vector<int> vs;
        int vsum = 0;
        for (int j = i; j >= 1; j--) {
            int sub = ari(j);
            while (ck >= sub) {
                ck -= sub;
                vsum += j;
                vs.push_back(j);
            }
        }
        if (ck > 0) continue;
        int size_need = vsum + vs.size() - 1;
        if (size_need > i) continue;

        vector<int> ans;
        for (auto x : vs) {
            while (x--) ans.push_back(2);
            ans.push_back(1);
        }
        if (!ans.empty()) ans.pop_back();
        while (int(ans.size()) < i) ans.push_back(1);

        cout << i << '\n';
        for (auto x : ans)
            cout << x << ' ';
        cout << '\n';
        return 0;
    }

    assert(0);

    return 0;
}