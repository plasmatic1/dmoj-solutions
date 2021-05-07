// ./another-contest-7-problem-1-lonely-users.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T; cin >> T;
    while (T--) {
        int x; cin >> x;
        if (x == 2) cout << "2\n";
        else cout << x-1 << '\n';
    }

    return 0;
}