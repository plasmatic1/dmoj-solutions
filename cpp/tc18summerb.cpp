#include <iostream>
using namespace std;

int main() {
    int c, d, e;
    cin >> c >> d >> e;
    if ((c & d) != d || (c ^ d) != e)
        cout << 0 << endl;
    else
        cout << (1 << __builtin_popcount(e)) << endl;
    return 0;
}