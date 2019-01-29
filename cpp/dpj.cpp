//============================================================================
// Name        : AtcoderDpJ.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 301;
int n, buf,
	c[4];
double dp[MAX][MAX][MAX];

double rec(int i, int j, int k){
	if(i == 0 && j == 0 && k == 0) return 0.;
	if(dp[i][j][k]) return dp[i][j][k];

	double tot = 1;

	if(i > 0) tot += rec(i - 1, j + 1, k) * ((double)i / n);
	if(j > 0) tot += rec(i, j - 1, k + 1) * ((double)j / n);
	if(k > 0) tot += rec(i, j, k - 1) * ((double)k / n);

	return dp[i][j][k] = tot / (1. - ((double)(n - i - j - k) / n));
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> buf;
		c[buf]++;
	}

	printf("%.12f\n", rec(c[3], c[2], c[1]));
}
