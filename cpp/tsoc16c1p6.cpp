//============================================================================
// Name        : JoeyAndBiology.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 1010;

int n, m,
	dp[MAX][MAX];
string a, b;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> a >> b;

	a = " " + a;
	b = " " + b;

	for (int i = 1; i <= n; ++i) {
		dp[i][0] = (int)ceil(i / 3.);
	}

	for (int i = 1; i <= m; ++i) {
		dp[0][i] = (int)ceil(i / 3.);
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if(a[i] == b[j])
				dp[i][j] = dp[i - 1][j - 1];
			else{
				int best = min(dp[i - 1][j - 1] + 1, min(dp[i][j - 1] + 1, dp[i - 1][j] + 1));

				if(j >= 2) best = min(best, dp[i][j - 2] + 1);
				if(i >= 2) best = min(best, dp[i - 2][j] + 1);
				if(j >= 3) best = min(best, dp[i][j - 3] + 1);
				if(i >= 3) best = min(best, dp[i - 3][j] + 1);

				dp[i][j] = best;
			}
		}
	}

//	printf("dp: [\n");
//	for(int i = 0; i < n + 1; i++){
//		printf("%d : ", i);
//		for(int j = 0; j < m + 1; j++){
//			printf("%d, ", dp[i][j]);
//		}
//		printf("\n");
//	}
//	printf("]\n");

	printf("%d\n", dp[n][m]);
}
