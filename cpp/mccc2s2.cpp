#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int len;
    string s;
    cin >> len >> s;

    deque<char> ret;
    ret.push_back(s[0]);
    for (int i = 1; i < len; i++) {
        if (s[i] <= ret.front()) 
            ret.push_front(s[i]);
        else
            ret.push_back(s[i]);
    }

    // print
    for (auto c : ret)
        cout << c;
    cout << '\n';

    return 0;
}