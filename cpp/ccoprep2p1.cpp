// ./cco-preparation-test-2-concatenation.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using ull = unsigned long long;

const int DIM = 3;
ull N, MOD;

struct vec {
    ull m[DIM];
    vec() { memset(m, 0, sizeof m); }
    ull operator()(int a) const { return m[a]; }
    ull& operator()(int a) { return m[a]; }
};
struct mat {
    ull m[DIM][DIM];
    mat() { memset(m, 0, sizeof m); }
    ull operator()(int a, int b) const { return m[a][b]; }
    ull& operator()(int a, int b) { return m[a][b]; }
    mat operator*(const mat o) const {
        mat ret;
        for (auto i = 0; i < DIM; i++)
            for (auto j = 0; j < DIM; j++)
                for (auto k = 0; k < DIM; k++)
                    ret(i, j) = (ret(i, j) + m[i][k] * o(k, j)) % MOD;
        return ret;
    }
    vec operator*(const vec o) const {
        vec ret;
        for (auto i = 0; i < DIM; i++)
            for (auto j = 0; j < DIM; j++)
                ret(i) = (ret(i) + m[i][j] * o(j)) % MOD;
        return ret;
    }
};
mat ID() {
    mat ret;
    for (auto i = 0; i < DIM; i++) ret(i, i) = 1;
    return ret;
}
mat exp(mat m, ull pow) {
    mat res = ID();
    for (; pow; pow >>= 1) {
        if (pow & 1) res = m * res;
        m = m * m;
    }
    return res;
}

/*
 * Variables:
 * [ans, ctr, 1]
 *
 * Transformation:
 * ans' = ans * d + ctr
 * ctr' = ctr + 1
 * 1' = 1
 */

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> MOD;

    vec ans;
    ans(1) = ans(2) = 1;

    ull d = 1;
    do {
        d *= 10;
        ull st = d/10, times = min(d-1, N) - st + 1;

        mat m;
        m(2, 2) = m(1, 1) = m(1, 2) = m(0, 1) = 1;
        m(0, 0) = d % MOD;

        ans = exp(m, times) * ans;
    } while (N >= d);

    cout << ans(0) << '\n';

    return 0;
}