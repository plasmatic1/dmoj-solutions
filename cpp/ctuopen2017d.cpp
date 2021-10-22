// a.yml
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using ld = long double;

/*
 *
 * y=x+b
 * b=y-x
 *
 * y=b-x
 * b=x+y
 */

const int MN = 1e5 + 1;
int N,
    X[MN], Y[MN];
map<int, int> fw, bw;

int cntAbove(vector<int> &v, int x) {
    return v.end() - upper_bound(v.begin(), v.end(), x);
}

void solve() {
    for (auto i = 0; i < N; i++) {
        cin >> X[i] >> Y[i];
        fw[Y[i]-X[i]]++;
        bw[X[i]+Y[i]]++;
    }

    ld tot = 0;
    for (auto i = 0; i < N; i++) {
        int v = fw[Y[i]-X[i]], v2 = bw[X[i]+Y[i]];

        ld cur = v-1+v2-1;
        tot += cur / N;
    }
    tot /= N;

    cout << fixed << setprecision(10) << tot << '\n';

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> N) {
        fw.clear();
        bw.clear();
        solve();
    }

    return 0;
}