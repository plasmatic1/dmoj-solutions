// ./many-messages.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int s, e, t; cin >> s >> e >> t;

    for (auto i = 0; i < 3; i++) {
        s += e;
        if (s >= t) {
            cout << s << '\n';
            return 0;
        }
    }

    cout << "Who knows...\n";

    return 0;
}