#include <iostream>
using namespace std;
int main() {
    int T = 5;
    while (T--) {
        int N;
        cin >> N;
        
        int cbit = 1, ans = N + (1 << __builtin_ctz(N));
        while (__builtin_popcount(ans) < __builtin_popcount(N)) {
            ans |= cbit;
            cbit <<= 1;
        }
        cout << ans << endl;
    }
}