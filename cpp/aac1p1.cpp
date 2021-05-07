// ./an-animal-contest-1-p1-alpaca-shapes.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int S, R; cin >> S >> R;
    double a = S*S, b = 3.14159*R*R;
    cout << (a<b ? "CIRCLE\n" : "SQUARE\n");

    return 0;
}