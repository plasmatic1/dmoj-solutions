//============================================================================
// Name        : BowlingForNumbers.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAX = 30001, MK = 501;
int t, n, k, w,
	pfx[MAX], dp[MK][MAX];

int go(int cur, int pas){
	if(dp[pas][cur]) return dp[pas][cur];
	if(cur >= n || pas == k) return 0;

	int best = 0;

	for(int i = 1; i <= n - cur; i++){
		best = max(best, pfx[cur + i] - pfx[max(cur, cur + i - w)] + go(cur + i, pas + 1));
	}

	return dp[pas][cur] = best;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> t;

	while(t--){
		cin >> n >> k >> w;

		memset(pfx, 0, sizeof pfx);
		memset(dp, 0, sizeof dp);

		for (int i = 1; i <= n; ++i) {
			cin >> pfx[i];
			pfx[i] += pfx[i - 1];
		}

		for (int i = 1; i <= k; ++i) {
			for (int j = 1; j < w; j++){
				dp[i][j] = pfx[j];
			}

			int best = 0;

//			printf(" -- i=%d\n", i);

			for (int j = w; j <= n; ++j) {
				dp[i][j] = pfx[j] - pfx[j - w] + best;
//				printf("j=%d best=%d\n", j, best);

				best = max(best, dp[i - 1][j - w + 1]);
			}
		}

//		for(int i = 0; i <= k; i++){
//			for(int j = 0; j <= n; j++){
//				printf("%d, ", dp[i][j]);
//			}
//			printf("\n");
//		}

		printf("%d\n", *max_element(dp[k], dp[k] + n + 1));
	}

	return 0;
}
