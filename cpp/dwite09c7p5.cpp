#include "bits/stdc++.h"
using namespace std;
int main() {
    for (int _ = 0; _ < 5; _++) {
        int N, K;
        cin >> N >> K;
        cout << (((K>>(N - 1)) & 1) ? "ON\n" : "OFF\n");
    }
}