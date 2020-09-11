#include <bits/stdc++.h>
using namespace std;

const int T = 8;

int x[T];

int main() {
    srand(time(NULL));
    for (auto i = 0; i < T; i++) x[i] = rand();

    cout << 1 << endl;
    cout << T << endl;
    cout << 2 << endl;
    cout << rand() << endl;
    cout << (x[0] + x[1] + x[2] + x[3] + x[4]) << endl; // don't optimize out?
    
    return 0;
}