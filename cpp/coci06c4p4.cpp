//============================================================================
// Name        : Zbrka.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MN = 1001, MC = 10001, MOD = 1000000007;
int n, c,
	dp[MN][MC];

inline int pos(int v){
	while(v < 0){
		v += MOD;
	}
	return v;
}

inline int psa(int row, int l, int r){
	if(l <= 0) return dp[row][r];
	return pos(dp[row][r] - dp[row][l - 1]) % MOD;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> c;

	for(int i = 0; i <= c; i++){
		dp[1][i] = 1;
	}

	for (int i = 2; i <= n; ++i) {
		for(int j = 0; j <= c; j++){
			dp[i][j] = psa(i - 1, j - i + 1, j);
		}

		for(int j = 1; j <= c; j++){
			dp[i][j] += dp[i][j - 1];
			dp[i][j] %= MOD;
		}
	}


	printf("%d\n", c > 0 ? pos(dp[n][c] - dp[n][c - 1]) % MOD : 1);
}

