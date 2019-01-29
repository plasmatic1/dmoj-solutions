//============================================================================
// Name        : AtcoderDpD.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX = 100001;
int n,w,bv,bw;
ll dp[MAX];

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin>>n>>w;

  while(n--){
    cin>>bw>>bv;
    for(int i=w;i>=bw;i--)dp[i]=max(dp[i],dp[i-bw]+bv);
  }

  cout<<dp[w]<<endl;
}
