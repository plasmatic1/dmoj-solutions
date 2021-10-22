// d.yml
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 1001;
int N,
    A[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> N) {
        for (auto i = 0; i < N; i++)
            cin >> A[i];

        if (N > 1) {
            int d = A[N-1]-A[N-2], ans = N-1;
            for (auto i = N-2; i >= 0; i--) {
                if (A[i+1]-A[i] == d) {
                    ans = i;
                }
                else
                    break;
            }

            cout << (ans+1) << '\n';
        }
        else
            cout << (1) << '\n';

    }

    return 0;
}