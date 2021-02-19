// ./mock-ccc-21-s1-edit-distance.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s, al; cin >> al >> s;
    set<string> os;
    for (int i = 0; i <= (int)s.length(); i++) {
        for (auto c : al) {
            string t = s;
            t.insert(t.begin() + i, c);
            os.insert(t);
        }
        if (i < (int)s.length()) {
            string t = s;
            t.erase(t.begin() + i);
            os.insert(t);
            for (auto c : al) {
                string t = s;
                t[i] = c;
                os.insert(t);
            }
        }
    }
    if (os.count(s)) os.erase(s);
    for (auto x : os) cout << x << '\n';

    return 0;
}