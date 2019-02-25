#include <bits/stdc++.h>

using namespace std;

#define ull unsigned long long

ull a, b, c, m = 42069900169420;

int main() {
    cin >> a >> b >> c;
    ull sum = a + b + c;
    
    printf("%llu", sum % m);
    
    return 0;
}