#include <bits/stdc++.h>

using namespace std;
#define ll long long

vector<int> nums;
string str;
int cn = 0;
ll total = 1;

int main() {
    cin >> str;
    
    // Procssing input
    
    for(int i = 0; i < str.length(); i++){
        if(str[i] == 'x'){
            nums.push_back(cn);
            cn = 0;
        }
        else{
            cn = (cn << 1) + (cn << 3);
            cn += (int)(str[i] - '0');
        }
    }
    
    nums.push_back(cn);
    sort(nums.begin(), nums.end());
    
    // Printing
    
    for(int i = 0; i + 1 < nums.size(); i++){
        printf("%dx", nums[i]);
    }
    printf("%d\n", nums[nums.size() - 1]);
    
    total = nums[0];
    for(int i = 1; i < nums.size(); i++){
        total *= (ll)nums[i];
    }
    printf("%lld\n", total);
    
    return 0;
}