//============================================================================
// Name        : pickit.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Scan and Debug
void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F &f, R&... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

const int MAX = 201;
int n = -1,
	arr[MAX], dp[MAX][MAX];

int rec(int l, int r){
	if(l > r) return 0;
	if(l == r) return arr[l - 1] + arr[l] + arr[l + 1];

	int &ret = dp[l][r];
	if(ret != -1) return ret;

	for(int i = l; i <= r; i++)
		ret = max(ret, rec(l, i - 1) + arr[i] + rec(i + 1, r));

	return ret += arr[l - 1] + arr[r + 1];
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n);

	while(n){
		for(int i = 0; i < n; i++)
			scan(arr[i]);

		memset(dp, -1, sizeof dp);
		printf("%d\n", rec(1, n - 2));

		scan(n);
	}
}