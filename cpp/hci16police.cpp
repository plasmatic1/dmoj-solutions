//============================================================================
// Name        : hci16police.cpp
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
int n, h, start = 0,
	loc[MAX];
ll dp[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> h;

	for(int i = 0; i < n; i++)
		cin >> loc[i];

	dp[0] = h;
	for(int i = 1; i < n; i++){
		ll bdx = loc[i] - loc[0];
		dp[i] = h + bdx * bdx;
		for(int j = start; j < i; j++){
			ll delta = loc[i] - loc[j + 1], alt = dp[j] + delta * delta + h;
			if(alt < dp[i]){
				start = j;
				dp[i] = alt;
			}
		}
	}

	printf("%lld\n", dp[n - 1]);
}