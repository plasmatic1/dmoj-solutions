#include <bits/stdc++.h>
using namespace std;
int n, m;
bool d[10002][10002];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    while (m--) {
        int x, y, w, h;
        cin >> x >> y >> w >> h;
        x++; y++;
        d[x][y] ^= 1;
        d[x + w][y] ^= 1;
        d[x][y + h] ^= 1;
        d[x + w][y + h] ^= 1;
    }
    int tot = 0;
    for (int i = 1; i < 10002; i++)
        for (int j = 1; j < 10002; j++)
            d[i][j] ^= d[i - 1][j] ^ d[i][j - 1] ^ d[i - 1][j - 1], tot += d[i][j];
    cout << tot << '\n';
}