//============================================================================
// Name        : AtcoderDpB.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

const int MAX = 100001;
int n, k,arr[MAX], dp[MAX];

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n >> k;

  memset(dp, 0x3f, sizeof(dp));
  dp[0] = 0;

  for(int i=0;i<n;i++)cin>>arr[i];
  for(int i=0;i<n;i++){
    for(int j=1;j<=k && i+j<n;j++){
      dp[i+j]=min(dp[i+j],dp[i]+abs(arr[i+j]-arr[i]));
    }
  }
  cout<<dp[n-1]<<endl;
}
