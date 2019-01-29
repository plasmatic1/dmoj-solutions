//============================================================================
// Name        : AtcoderDpH.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const int MAX = 1001;
int h, w;
ll dp[MAX][MAX];
char grid[MAX][MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> h >> w;

	for (int i = 0; i < h; ++i) {
		cin >> grid[i];
	}

	dp[0][0] = 1;

	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			dp[i][j] %= MOD;

			if(grid[i + 1][j] != '#') dp[i + 1][j] += dp[i][j];
			if(grid[i][j + 1] != '#') dp[i][j + 1] += dp[i][j];
		}
	}

	printf("%lld\n", dp[h - 1][w - 1]);
}
