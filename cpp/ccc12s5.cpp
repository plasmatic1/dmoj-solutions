//============================================================================
// Name        : ccc12s5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 51;
int r, c, k, ba, bb,
	dp[MAX][MAX];
bool bad[MAX][MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> r >> c >> k;

	for (int i = 0; i < k; ++i) {
		cin >> ba >> bb;
		bad[ba][bb] = true;
	}

	dp[0][1] = 1;
	for(int i = 1; i <= r; i++)
		for(int j = 1; j <= c; j++)
			if(!bad[i][j]) dp[i][j] = dp[i - 1][j] + dp[i][j - 1];

	printf("%d\n", dp[r][c]);

	return 0;
}