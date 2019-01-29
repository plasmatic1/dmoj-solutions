//============================================================================
// Name        : AtCoderDpN.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

// too hard to find in mc

const int MAX = 401;
int n;
ll pfx[MAX], dp[MAX][MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 1; i <= n; ++i) {
		cin >> pfx[i];
		pfx[i] += pfx[i - 1];
	}

	for (int i = 1; i < n; ++i) {
		int end = n - i;
		for (int l = 1; l <= end; ++l) {
			ll best = LLONG_MAX;
			int r = l + i;

			for(int k = l + 1; k <= r; k++){
				best = min(best, dp[l][k - 1] + dp[k][r]);
			}

			dp[l][r] = best + pfx[r] - pfx[l - 1];
		}
	}

	printf("%lld\n", dp[1][n]);
}
