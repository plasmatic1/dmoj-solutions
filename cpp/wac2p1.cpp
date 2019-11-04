#include <bits/stdc++.h>

using namespace std;

const string days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
unordered_map<string, int> mp;

int main() {
    for (int i = 0; i < 7; i++)
        mp[days[i]] = i;
    
    string s;
    cin >> s;
    
    cout << days[(mp[s] + 1) % 7] << '\n';
    
    return 0;
}
