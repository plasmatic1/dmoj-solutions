#include <bits/stdc++.h>

using namespace std;

int main() {
    int N; cin >> N; string s; cin >> s;
    for (auto c : s)
        cout << (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u' && c != 'y');
    cout << '\n';
    return 0;
}