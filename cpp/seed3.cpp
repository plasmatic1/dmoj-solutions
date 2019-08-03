#include <bits/stdc++.h>

using namespace std;

const int MN = 1e5 + 10;
int n, k, q, ba, bb, bc,
    pfx[MN];

int main() {
    ios_base::sync_with_stdio(true);
    cin.tie(NULL);

    cin >> n >> k >> q;

    for (int i = 0; i < q; i++) {
        cin >> ba >> bb >> bc;
        pfx[ba] += bc;
        pfx[bb + 1] -= bc;
    }

    for (int i = 1; i <= n; i++)
        pfx[i] += pfx[i - 1];
    
    int tot = 0;
    for (int i = 1; i <= n; i++)
        tot += pfx[i] < k;
    cout << tot << "\n";
}