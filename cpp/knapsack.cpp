//============================================================================
// Name        : AKnapsackProblem.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MV = 5001, MB = 1 << 30;

int n, m, ba, bb, bc;
ll best = LLONG_MIN,
	dp[MV], no[MV], c[MV], v[MV];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 0; i < n; ++i) {
		cin >> no[i] >> c[i] >> v[i];

		if((ll)no[i] * (ll)c[i] > MV){
			for(int j = c[i]; j < MV; j++){
				dp[j] = max(dp[j], dp[j - c[i]] + v[i]);
			}
		}
		else{
			ll j = 1;
			while(j < no[i]){
				ll cc = (ll)c[i] * (ll)j, vv = (ll)v[i] * (ll)j;

				for(int k = MV - 1; k >= cc; k--){
					dp[k] = max(dp[k], dp[k - cc] + vv);
				}

				no[i] -= j;
				j <<= 1;
			}

			ll cc = (ll)c[i] * (ll)no[i], vv = (ll)v[i] * (ll)no[i];

			for(int k = MV - 1; k >= cc; k--){
				dp[k] = max(dp[k], dp[k - cc] + vv);
			}
		}
	}

	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb;

		best = max(best, dp[ba] - bb);
	}

	printf("%lld\n", best);
}
