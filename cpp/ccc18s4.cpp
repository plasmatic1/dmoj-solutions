//============================================================================
// Name        : BalancedTrees.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

int n;
unordered_map<int, ll> dp;

ll cnt(int v){
	if(v < 3){
		return 1;
	}

	if(dp[v]){
		return dp[v];
	}

	ll total = 0;
	int i = v / 2, last = i + 1;

//	printf("v=%d\n", v);

	while(true){
		int ccount = v / i;

		total += cnt(i) * (ccount - (v / last));
//		printf("coeff=%d\n", ccount - (v / last));

		if(i == 1) break;

		int nxccount = v / (i - 1), next = -1;

		if(ccount == nxccount){
			next = v / (ccount + 1);
		}
		else{
			next = i - 1;
		}

//		printf("i=%d next=%d ccount=%d nxccount=%d\n", i, next, ccount, nxccount);

		last = i;
		i = next;
	}

	return dp[v] = total;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

//	dp[5] = 4;
//	dp[3] = 2;

	printf("%lld\n", cnt(n));
}
