#include <bits/stdc++.h>
using namespace std;
int main() {
    map<int, int> mp;
    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        int x; cin >> x;
        mp[x]++;
    }
    for (auto p : mp) cout << p.first << ' ';
    for (auto it = mp.rbegin(); it != mp.rend(); it++) {
        int c = it->second-1;
        while (c--) cout << it->first << ' ';
    }
    cout << '\n';
    return 0;
}