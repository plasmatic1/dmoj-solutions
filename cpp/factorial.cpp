//============================================================================
// Name        : FastFactorialCalculator.cpp (1 and 2)
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> p;

const ull MOD_V = 1ULL << 32;

int n;
ull buf;
unordered_map<ull, ull> dp;

ull fact(ull x){
	ull dpv = dp[x];
	if(dpv != 0){
		return dpv;
	}

	return (x * fact(x - 1)) % MOD_V;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	dp[1] = 1;

	for (int i = 0; i < n; ++i) {
		cin >> buf;

		printf("%llu\n", fact(buf));
	}
}
