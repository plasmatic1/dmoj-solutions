//============================================================================
// Name        : SantasJourney.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;
const int MAX = 1000001;
int n, m,
  a[MAX], b[MAX], dp[MAX], par[MAX], prevs[MAX];
vector<int> path;


int main(){
  cin >> n >> m;

  for(int i = 1; i <= m; i++){
    cin >> a[i] >> b[i];
  }

  memset(dp, 0x3f, sizeof(dp));

  for(int i = 1; i <= m; i++){
    if(a[i] == a[1]){
      dp[i] = 1;
      par[i] = -1;
    }
  }

  for(int i = 1; i <= m; i++){
    int minv = prevs[a[i]];
    if(dp[minv] + 1 < dp[i]){
      dp[i] = dp[minv] + 1;
      par[i] = minv;
    }

    if(dp[i] < dp[prevs[b[i]]]){
      prevs[b[i]] = i;
    }
  }

  // printf("dp: [");
  // for(int i = 1; i <= m; i++){
  //     printf("%d, ", dp[i]);
  // }
  // printf("]\n");

  int minv = INT_MAX, mini = -1;
  for(int i = 1; i <= m; i++){
    if(b[i] == b[m] && dp[i] < minv){
      minv = dp[i];
      mini = i;
    }
  }

  printf("%d\n", dp[mini]);

  int cur = mini;
  while(cur != -1){
    path.push_back(cur);
    cur = par[cur];
  }

  int psize = path.size();
  for(int i = psize - 1; i >= 0; i--){
    printf("%d %d\n", a[path[i]], b[path[i]]);
  }

  return 0;
}
