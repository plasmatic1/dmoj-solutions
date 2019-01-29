//============================================================================
// Name        : CombiningRiceballs.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 401;
int n,
	arr[MAX], dp[MAX][MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	memset(dp, -1, sizeof(dp));

	for(int i = 1; i <= n; i++){
		cin >> dp[1][i];
	}

	for(int i = 2; i <= n; i++){
		for (int j = 1; j <= n - i + 1; ++j) {
			int maxpossib = -1;

			for (int k = j; k < j + i - 1; ++k) {
				int ball1 = dp[k - j + 1][j], ball2 = dp[j + i - 1 - k][k + 1];

				if(ball1 != -1 && ball1 == ball2){
					maxpossib = max(maxpossib, ball1 + ball2);
				}

				if(i > 2){
					for(int l = k + 2; l < i + j; l++){
						ball2 = dp[i + j - l][l];
						int mid = dp[l - k - 1][k + 1];

						if(ball1 != -1 && ball1 == ball2 && mid != -1){
							maxpossib = max(maxpossib, ball1 + ball2 + mid);
						}
					}
				}
			}

			dp[i][j] = maxpossib;
		}
	}

	// Getting max value

	int maxv = -1;

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
//			printf("%d ", dp[i][j]);
			maxv = max(maxv, dp[i][j]);
		}
//		printf("\n");
	}

	printf("%d\n", maxv);
}
