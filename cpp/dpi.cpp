//============================================================================
// Name        : AtcoderDpI.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 3000;
int n;
double tot = 0.,
		dp[MAX][MAX], c[MAX];



int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;

	for (int i = 1; i <= n; ++i) {
		cin >> c[i];
	}

	dp[0][0] = 1;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			dp[i + 1][j + 1] += c[i + 1] * dp[i][j];
			dp[i + 1][j] += (1 - c[i + 1]) * dp[i][j];
		}
	}

	for (int i = n / 2 + 1; i <= n; ++i) {
		tot += dp[n][i];
	}

	printf("%.12f\n", tot);
}
