//============================================================================
// Name        : AtcoderDpA.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

const int MAX = 100001;
int n, arr[MAX], dp[MAX];

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n;

  memset(dp, 0x3f, sizeof(dp));
  dp[0] = 0;

  for(int i=0;i<n;i++)cin>>arr[i];
  for(int i=0;i<n-1;i++){
    dp[i+1]=min(dp[i+1],dp[i]+abs(arr[i+1]-arr[i]));
    if(i<n-2)dp[i+2]=min(dp[i+2],dp[i]+abs(arr[i+2]-arr[i]));
  }
  cout<<dp[n-1]<<endl;
}
