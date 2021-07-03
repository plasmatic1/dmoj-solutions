// ./dmopc-19-contest-5-p3-captivating-construction-challenge.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }

const int MN = 2001;
int R, C;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> R >> C;

    // assume one side of rectangle goes from (a,b) to (a+i, b+j)
    ll ans = 0;
    for (auto i = 1; i <= R; i++) {
        for (auto j = 0; j <= C; j++) { // i,j -> length of one side of rectangle
            int dx = j/gcd(i, j), dy = i/gcd(i, j), cx = i+dx, cy = j+dy; // loop over all possible other side lengths
            // this is kinda like harmonic series optimization but in 2D I believe? 
            // If you expand out the math, I think this works
            while (cx <= R && cy <= C) {
                ans += ll(R-cx) * (C-cy);

                cx += dx;
                cy += dy;
            }
        }
    }

    cout << ans << '\n';

    return 0;
}