//============================================================================
// Name        : BobAndFrenchClass.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 100001;
int n,
	dp[MAX][3], en[MAX], fr[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> fr[i];
	}

	for (int i = 0; i < n; ++i) {
		cin >> en[i];
	}

	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j < 3; ++j) {
			dp[i][j] = INT_MIN;
		}
	}

	dp[0][0] = 0;

	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j < 3; ++j) {
			if(dp[i][j] != INT_MIN){
				if(j < 2){
					dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + fr[i]);
				}

				dp[i + 1][0] = max(dp[i + 1][0], dp[i][j] + en[i]);
			}
		}
	}

//	printf("dp: [\n");
//	for(int i = 0; i < n + 1; i++){
//		for(int j = 0; j < 3; j++){
//			printf("%d, ", dp[i][j]);
//		}
//		printf("\n");
//	}
//	printf("]\n");

	printf("%d\n", *max_element(dp[n], dp[n] + 3));
}
