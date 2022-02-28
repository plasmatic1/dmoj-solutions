//============================================================================
// Name        : ccoprep16c2q2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 100001, MBIT = 32;
int n, buf, best = 0,
	dp[MAX], bestDPs[MBIT];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> buf;

		for (int j = 0; j < MBIT; ++j)
			if((buf >> j) & 1)
				dp[i] = max(dp[i], bestDPs[j] + 1);

		for (int j = 0; j < MBIT; ++j)
			if((buf >> j) & 1)
				bestDPs[j] = max(bestDPs[j], dp[i]);

		best = max(best, dp[i]);
	}

	printf("%d\n", best);
}