//============================================================================
// Name        : dwite09c6p4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int T =
#ifndef ONLINE_JUDGE
2;
#else
5;
#endif

const int MAX = 11, MM = 101;
int n, m, bc,
	dp[MM];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	while(T--){
		cin >> m >> n;

		memset(dp, 0x3f, sizeof dp);
		dp[0] = 0;
		for(int i = 0; i < n; i++){
			cin >> bc;
			for(int j = bc; j <= m; j++)
				dp[j] = min(dp[j], dp[j - bc] + 1);
		}

		printf("%d\n", dp[m]);
	}
}