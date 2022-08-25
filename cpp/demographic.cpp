// > It is highly recommended to use fast input.
// no.

#include <bits/stdc++.h>

using namespace std;

const int MN = 3e5 + 1;
int N, Q,
    A[MN];
    
int get(int k) {
    return upper_bound(A, A+N, k) - A;
}

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> A[i];
    sort(A, A+N);
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        int l, r; cin >> l >> r;
        cout << (get(r) - get(l-1)) << endl;
    }
    
    return 0;
}