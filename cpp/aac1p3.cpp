// ./an-animal-contest-1-p3-happy-alpacas.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, X;
    cin >> N >> X;
    if (X > N) {
        cout << "-1\n";
        return 0;
    }
    X = N-X;
    if (X % 2) cout << "-1\n";
    else {
        int left = N;
        auto O = [&] (int k) {
            left--;
            cout << k << " \n"[left == 0];
        };
        for (auto i = 0; i < X/2; i++) O(0), O(1);
        for (auto i = 0; i < N-X; i++) O(0);
        cout << '\n';
    }

    return 0;
}