//============================================================================
// Name        : AtcoderDpC.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

const int MAX = 100001;
int n, k,arr[3][MAX], dp[3][MAX];

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n;

  for(int i=1;i<=n;i++)cin>>arr[0][i]>>arr[1][i]>>arr[2][i];

  //dp[0][1]=arr[0][1];
  //dp[1][1]=arr[1][1];
  //dp[2][1]=arr[2][1];

  for(int i=0;i<n;i++){
    for(int j=0;j<3;j++){
      for(int k=0;k<3;k++){
        if(j==k)continue;
      	dp[k][i+1]=max(dp[k][i+1], dp[j][i]+arr[k][i+1]);
      }
    }
  }

  cout<<max(dp[0][n],max(dp[1][n],dp[2][n]))<<endl;
}
