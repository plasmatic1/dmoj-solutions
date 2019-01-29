//============================================================================
// Name        : PhantomFight.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 5001, MV = 10001;
int n, m, bc, br,
	dp[2][MV];
bool curr = false;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	memset(dp, -1, sizeof(dp));
	dp[curr][m] = 0;

	for (int i = 0; i < n; ++i) {
		cin >> bc >> br;

		bool next = !curr;

		for (int j = 0; j < MV; ++j) {
			dp[next][j] = dp[curr][j];
		}

		for (int j = 0; j < MV; j++) {
			if(dp[curr][j] == -1){
				continue;
			}

			if(j - bc >= 0){
				dp[next][j - bc + br] = max(dp[curr][j - bc + br], dp[curr][j] + 1);
			}
		}

		curr = next;
	}

	int maxc = -1, maxm = -1;

	for (int i = 0; i < MV; ++i) {
		if(dp[curr][i] > maxc){
			maxc = dp[curr][i];
			maxm = i;
		}
		else if(dp[curr][i] == maxc){
			maxm = max(maxm, i);
		}
	}

	printf("%d %d\n", maxc, maxm);
}
