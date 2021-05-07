// ./dmopc-20-contest-5-p1-home-row.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s, t;
    cin >> s >> t;

    int len = min(s.length(), t.length()), mat = 0;
    for (auto i = 0; i < len; i++) {
        if (s[i] == t[i]) mat++;
        else break;
    }

    cout << s.length() + t.length() - 2*mat << '\n';

    return 0;
}