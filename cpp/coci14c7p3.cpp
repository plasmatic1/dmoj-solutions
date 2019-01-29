//============================================================================
// Name        : ACM.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
//#define DEBUG

using namespace std;

const int MAX = 150001, orderings[6][3] = {
		{0, 1, 2},
		{0, 2, 1},
		{1, 0, 2},
		{1, 2, 0},
		{2, 0, 1},
		{2, 1, 0}
};
int n,
	arr[3][MAX], dp[3][MAX];

int cost = INT_MAX;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < 3; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> arr[i][j];
		}
	}

	//DP

	for(const int* ordering : orderings){
		//Init dp
		for (int i = 0; i < 3; ++i) {
			fill(dp[i], dp[i] + n + 1, INT_MAX);
		}
		dp[ordering[0]][0] = 0;

		//dp seqience

		int ci = ordering[0];
		for (int i = 1; i <= n; ++i) {
			dp[ci][i] = dp[ci][i - 1] + arr[ci][i];
		}

		for (int i = 1; i < 3; ++i) {
			ci = ordering[i];
			int pi = ordering[i - 1];
			for (int j = i + 1; j <= n; ++j) {
				dp[ci][j] = min(dp[ci][j - 1], dp[pi][j - 1]) + arr[ci][j];
			}
		}

		//Debug
#ifdef DEBUG
		printf("ordering: ");
		for (int i = 0; i < 3; ++i) {
			printf("%d, ", ordering[i]);
		}
		printf("\n");
		printf("dp: [\n");
		for(int i = 0; i < 3; i++){
			printf("%d : ", i);
			for(int j = 0; j < n + 1; j++){
				printf("%d, ", dp[i][j]);
			}
			printf("\n");
		}
		printf("]\n");
		printf("cost=%d\n", dp[ordering[2]][n]);
#endif

		cost = min(cost, dp[ordering[2]][n]);
	}

	printf("%d\n", cost);
}
