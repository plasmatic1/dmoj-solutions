//============================================================================
// Name        : PoliticalInstability.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct q{
  int a, b;
};

const int MAX = 600010;
int n, d, nd, ba, bb, mbit = 1,
  arr[MAX];
ll tot = 0,
  tree[MAX], ctree[MAX];
vector<int> ranks;
q queries[MAX];

inline int grank(int x){
  return lower_bound(ranks.begin(), ranks.end(), x) - ranks.begin();
}

inline void add(ll *tre, int x, ll v){
  x = grank(x);

  for(; x <= nd; x += x & -x){
    tre[x] += v;
  }
}

inline ll sum(ll *tre, int x){
  ll summ = 0;
  for(; x > 0; x -= x & -x){
    summ += tre[x];
  }
  return summ;
}

#define tsum(x) (sum(tree, (x)))
#define csum(x) (sum(ctree, (x)))
#define tadd(x, v) add(tree, (x), (v))
#define cadd(x, v) add(ctree, (x), (v))

inline void run(){
  ll goal = (tot / 2) + (tot % 2);

  int idx = 0;
  ll ctot = 0;

  for(int i = mbit; i > 0; i >>= 1){
    int alt = idx | i;

    if(alt <= nd && ctot + tree[alt] < goal){
      ctot += tree[alt];
      idx = alt;
    }
  }

  int lastsum = csum(idx + 1) - csum(idx);

  if(lastsum > 1){
    ll lasttot = tsum(idx), val = ranks[idx + 1];

    int l = 0, r = lastsum + 1;

    while(l + 1 < r){
      int mid = (l + r) >> 1;

      if(lasttot + val * mid < goal){
        l = mid;
      }
      else{
        r = mid;
      }
    }

    // printf("idx=%d l=%d r=%d\n", idx, l, r);
    printf("%lld\n", n - (csum(idx) + l));
  }
  else{
    // printf("idx=%d, lastsum=%d\n", idx, lastsum);
    printf("%lld\n", n - csum(idx));
  }
}

int main(){
  cin >> n >> d;

  set<int> tranks;
  tranks.insert(-1);

  for(int i = 1; i <= n; i++){
    cin >> ba;

    arr[i] = ba;
    tot += ba;
    tranks.insert(ba);
  }

  for(int i = 0; i < d; i++){
    cin >> ba >> bb;

    queries[i] = {ba, bb};
    tranks.insert(bb);
  }

  ranks = vector<int>(tranks.begin(), tranks.end());

  nd = ranks.size() - 1;
  for(; mbit <= nd; mbit <<= 1){}

  // Processing

  for(int i = 1; i <= n; i++){
    tadd(arr[i], arr[i]);
    cadd(arr[i], 1);
  }

  run();

  for(int i = 0; i < d; i++){
    int a = queries[i].a, b = queries[i].b;

    tadd(arr[a], -arr[a]);
    cadd(arr[a], -1);

    tot += b - arr[a];

    arr[a] = b;

    tadd(b, b);
    cadd(b, 1);

    run();
  }

  return 0;
}
