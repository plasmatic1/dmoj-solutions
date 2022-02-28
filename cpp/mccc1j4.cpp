#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int sz;
    string s;
    vector<int> v;
    v.push_back(-INF);
    cin >> sz >> s;
    for (int i = 0; i < sz; i++)
        if (s[i] == '1')
            v.push_back(i);
    v.push_back(INF);
    ll tot = 0;
    for (int i = 0; i < sz; i++) {
        auto c = lower_bound(v.begin(), v.end(), i), p = c; p--;
        // printf("i=%d *c=%d *p=%d\n", i, *c, *p);
        tot += min(*c - i, i - *p);
    }
    cout << tot << '\n';

    return 0;
}