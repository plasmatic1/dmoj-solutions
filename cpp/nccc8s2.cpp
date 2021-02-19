// ./mock-ccc-21-s2-colorful-strings.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const ll MOD = 1e9 + 7;
ll fre[26];
string s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> s;
    for (auto c : s) fre[c - 'a']++;
    ll ans = 1;
    for (int i = 0; i < 26; i++)
        ans = (ans * (fre[i]+1)) % MOD;
    cout << ans << '\n';

    return 0;
}