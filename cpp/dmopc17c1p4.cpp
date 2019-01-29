//============================================================================
// Name        : Quests.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
#define ll long long

using namespace std;

const ll INF = 0x3f3f3f3f;
const int MV = 5001;
int n, h, bg, bh, bq, bt, curr = 0;
ll dp[2][MV];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> h;

	for (int i = 0; i < n; ++i) {
		int next = !curr;

		cin >> bg >> bh >> bq >> bt; // rew, cost, rew, cost

		for(int j = 0; j < MV; j++){
			dp[next][j] = -INF;

			if(j >= bh){
				dp[next][j] = max(dp[next][j], dp[curr][j - bh] + (ll)bg);
			}
			if(j >= bt + bh){
				dp[next][j] = max(dp[next][j], dp[next][j - bt] + (ll)bq);
			}
		}

		for(int j = 0; j < MV; j++){
			dp[next][j] = max(dp[next][j], dp[curr][j]);
		}

		curr = next;
	}

	printf("%lld\n", dp[curr][h]);
}
