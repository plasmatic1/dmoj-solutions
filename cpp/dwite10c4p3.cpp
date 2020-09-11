#include <iostream>
using namespace std;
int main() {
    int T = 5;
    while (T--) {
        int N;
        cin >> N;
        int ans = N + (N & -N), cbit = 1;
        while (__builtin_popcount(ans) < __builtin_popcount(N)) {
            ans |= cbit;
            cbit <<= 1;
        }
        cout << ans << endl;
    }
    return 0;
}