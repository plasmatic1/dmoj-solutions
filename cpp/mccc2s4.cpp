// fuck you, evan

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 1e5 + 1;
int N,
    val[MN];

vector<int> nums[MN]; // nums by modulus

ll medianSum(vector<int> &v) {
    int sz = v.size(); 
    sort(v.begin(), v.end());
    int median = v[sz / 2];
    ll tot = 0;
    for (int x : v)
        tot += abs(x - median); //, printf("%d ", x);
    return tot;
}

ll run(int shift) {
    if (shift == N) return LLINF;
    ll tot = 0;
    for (int j = 0; j < N; j++)
        nums[j % shift].push_back(val[j]);
    for (int j = 0; j < shift; j++)
        tot += medianSum(nums[j]);
    for (int j = 0; j < shift; j++)
        nums[j].clear();
    // printf("shift=%d tot=%lld\n", shift, tot);
    return tot;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> val[i];
    }

    if (N == 1) {
        cout << "0\n";
        return 0;
    }

    // do some dumb stuff    
    ll best = LLINF;
    for (int i = 1; i * i <= N; i++) {
        if (N % i == 0) {
            best = min(best, run(i));
            if (i * i != N)
                best = min(best, run(N / i));
        }
    }

    cout << best << '\n';

    return 0;
}