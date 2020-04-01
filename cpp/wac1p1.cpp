#include <bits/stdc++.h>
using namespace std;
int main() {
    int t; cin >> t;
    while (t--) {
        long long m; cin >> m;
        long long l = 0, r = 2e9;
        while (l + 1 < r) {
            long long mid = (l + r) / 2;
            if ((mid - 1) * mid / 2 >= m)
                r = mid;
            else
                l = mid;
        }
        cout << r << endl;
    }
}