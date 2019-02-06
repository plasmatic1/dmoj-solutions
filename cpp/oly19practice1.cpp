//============================================================================
// Name        : CombiningNumbers.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 300001, MV = 61;
int n, buf, best = 0,
	dp[MV][MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;

	for (int i = 1; i <= n; ++i) {
		cin >> buf;
		dp[buf][i] = i + 1;
		best = max(best, buf);
	}

	for (int i = 2; i < MV; ++i) {
		for (int j = 1; j <= n; ++j) {
			dp[i][j] = max(dp[i][j], dp[i - 1][dp[i - 1][j]]);
			if(dp[i][j]) best = max(best, i);
		}
	}

	printf("%d\n", best);

	return 0;
}

/*
 * max number is logn + 40, 58
 * dp[val][i]
 * starting from i, get val
 * stores endpoint
 *
 * like lca binary lifting
 * to check if dp[val][i],
 *      endpt = dp[val-1][i]  first endpoint
 *      if dp[val-1][endpt]
 *          yes
 *
 */