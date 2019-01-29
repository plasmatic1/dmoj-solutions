//============================================================================
// Name        : NotEnoughTime.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 2001, TMAX = 10001;
int n, t, old = 1,
	dp[2][TMAX], profits[MAX][3], costs[MAX][3];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> t;

	for(int i = 1; i <= n; i++){
		cin >> costs[i][0] >> profits[i][0] >> costs[i][1] >> profits[i][1] >> costs[i][2] >> profits[i][2];
	}

	for(int i = 1; i <= n; i++){
		int newr = !old;

		for(int j = 1; j <= t; j++){
			int best = max(dp[old][j - 1], dp[old][j]);

			for (int k = 0; k < 3; ++k) {
				if(costs[i][k] <= j){
					best = max(best, dp[old][j - costs[i][k]] + profits[i][k]);
				}
			}

			dp[newr][j] = best;
		}

		old = newr;
	}

	printf("%d\n", dp[old][t]);
}
