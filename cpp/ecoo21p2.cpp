// ./dna-derren.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int N;
string s;

bool ok(int i) {
    return (s[i] == 'A') != (s[i-1] == 'A');
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> s;
    N = s.length();

    for (auto i = 0; i < N; ) {
        int j = i+1;
        while (j < N && ok(j)) j++;
        for (auto k = i; k < j; k++) cout << s[k];
        cout << " \n"[j >= N];

        i = j;
    }
    cout << '\n';

    return 0;
}