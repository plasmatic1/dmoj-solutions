#include <bits/stdc++.h>

using namespace std;

int main(){
ios_base::sync_with_stdio(false);
cin.tie(NULL);
int n, arr[5001], dp[5001];
cin >> n;

for(int i = 1; i <= n; i++)cin>>arr[i];

memset(dp,0,sizeof dp);
int gay = -1;
arr[0]=-999999999;
for(int i = 1; i <=n;i++){
for(int j = 0; j < i; j++){
if(arr[j] < arr[i]) dp[i] = max(dp[i], dp[j] + 1);
}
gay = max(gay, dp[i]);
}
cout<<gay<<endl;
return 0;
}