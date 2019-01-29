//============================================================================
// Name        : MagicalBribery.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
//#define DEBUG

using namespace std;

typedef long long ll;

const int MAX = 1001;
int n, buf,
	dp[MAX][MAX], cards[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;

	for (int i = 1; i <= n; ++i) {
		cin >> cards[i];
	}

	//i is card being tested, j is cards available
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if(j < i){
				dp[i][j] = dp[i - 1][j];
				continue;
			}

			dp[i][j] = max(dp[i - 1][j],
					max(dp[i][j - i], dp[i - 1][j - i]) + cards[i]);
		}
	}

#ifdef DEBUG
	printf("dp: [\n");
	for(int i = 0; i <= n; i++){
		for(int j = 0; j <= n; j++){
			printf("%d, ", dp[i][j]);
		}
		printf("\n");
	}
	printf("]\n");
#endif

	printf("%d\n", dp[n][n]);
}
