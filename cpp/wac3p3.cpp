#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using psi = pair<string, int>;

bool cmp(const psi &a, const psi &b) {
    return a.first.length() > b.first.length();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    vector<psi> combo;
    int m;

    cin >> s >> m;
    for (int i = 0; i < m; i++) {
        string c; int p;
        cin >> c >> p;
        combo.push_back({c, p});
    }
    sort(combo.begin(), combo.end(), cmp);

    int pts = s.length(), ptr = 0, n = s.length();
    while (ptr < n) {
        int comblen = 1;
        for (int i = 0; i < m; i++) {
            if ((size_t)n - ptr < combo[i].first.length())
                continue;
            if (s.substr(ptr, combo[i].first.length()) == combo[i].first) {
                pts += combo[i].second;
                comblen = combo[i].first.length();
                break;
            }
        }
        // printf("ptr=%d comblen=%d\n", ptr, comblen);

        ptr += comblen;
    }
    cout << pts << '\n';

    return 0;
}