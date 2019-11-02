#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    int p[n+1];
    p[0]=0;
    for (int i = 1; i <= n; i++) cin >> p[i];
    for (int i = 1; i <= n; i++) p[i] += p[i - 1];
    int q; cin>>q;
    while (q--) {
        int a, b;
        cin>>a>>b; a++; b++;
        cout << (p[b]-p[a-1])<<'\n';
    }
}
