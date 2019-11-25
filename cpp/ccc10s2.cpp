#include <bits/stdc++.h>
using namespace std;

int main() {
    int k, n;
    cin >> k;

    string let[k], code[k];
    for (int i = 0; i < k; i++) {
        cin >> let[i] >> code[i];
    }

    string s;
    cin >> s;
    n = s.length();

    int st = 0;
    while (st < n) {
        for (int i = 0; i < k; i++) {
            if (s.substr(st, code[i].length()) == code[i]) {
                cout << let[i];
                st += code[i].length();
                break;
            }
        }
    }

    cout << '\n';
    return 0;
}
