// ./another-contest-7-problem-2-code-review.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 5e3 + 1;
int N,
    P[MN];
mt19937 mt(26022021);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    iota(P, P+N, 1);
    shuffle(P, P+N, mt);
    uniform_int_distribution<int> dis(1, N);

    int res;
    do {
        for (auto i = 0; i < N; i++)
            cout << P[i] << " \n"[i == N-1];
        cout.flush();
        cin >> res;

        if (res) {
            int target = res;
            while (target == res) target = dis(mt);
            swap(P[res-1], P[target-1]);
        }
    } while (res);

    return 0;
}