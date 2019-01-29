//============================================================================
// Name        : BallSculpture.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;
const int MAX = 1000001;
int n, m,
  a[MAX], b[MAX], cnt[MAX + 1];

int main(){
  cin >> n >> m;
  cnt[1] = m;

  for(int i = 1; i <= n; i++){
    cin >> a[i] >> b[i];
  }

  for(int i = 1; i <= n; i++){
    cnt[a[i]] += (cnt[i] / 2) + (cnt[i] % 2);
    cnt[b[i]] += cnt[i] / 2;
  }

  for(int i = 1; i <= n; i++){
    printf("%d", cnt[i] % 2);
  }
  printf("\n");

  return 0;
}
