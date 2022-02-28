#include "bits/stdc++.h"
using namespace std;

using P = pair<string, string>;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int X, Y, G;

int main() {
    vector<P> same, diff;
    set<P> groups;

    cin >> X;
    while (X--) {
        string s, t; cin >> s >> t;
        same.emplace_back(s, t);
    }

    cin >> Y;
    while (Y--) {
        string s, t; cin >> s >> t;
        diff.emplace_back(s, t);
    }

    cin >> G;
    while (G--) {
        string a, b, c; cin >> a >> b >> c;
        groups.emplace(a, b);
        groups.emplace(b, a);
        groups.emplace(c, b);
        groups.emplace(b, c);
        groups.emplace(a, c);
        groups.emplace(c, a);
    }

    int ans = 0;
    for (auto p : same)
        ans += !groups.count(p);
    for (auto p : diff)
        ans += groups.count(p);

    cout << ans << '\n';

    return 0;
}