// c.yml
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

ll S;
char T;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> S) {
        cin >> T;

        if (T == 'K') {
            if (S == 1) 
                cout << (1) << '\n';
            else 
                cout << (4) << '\n';
        }
        else if (T == 'N') {
            if (S <= 2)
                cout << (1) << '\n';
            else
                cout << (2) << '\n';
        }
        else if (T == 'B') {
            cout << (S) << '\n';
        }
        else if (T == 'R') {
            cout << (S) << '\n';
        }
        else assert(0);
    }

    return 0;
}