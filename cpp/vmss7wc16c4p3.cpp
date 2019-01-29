//============================================================================
// Name        : RestoringReputation.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 1001;

int n, m, d, iv, r,
	dp[MAX][MAX];
string a, b;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> d >> iv >> r >> a >> b;
	n = a.length();
	m = b.length();

	a = " " + a;
	b = " " + b;

	for(int i = 1; i <= n; i++){
		dp[i][0] = i * d;
	}

	for(int i = 1; i <= m; i++){
		dp[0][i] = i * iv;
	}

	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(a[i] == b[j]){
				dp[i][j] = dp[i - 1][j - 1];
			}
			else{
				dp[i][j] = min(dp[i - 1][j - 1] + r, min(dp[i - 1][j] + d, dp[i][j - 1] + iv));
			}
		}
	}

//	for(int i = 0; i <=n;i++){
//		for(int j=0;j<=m;j++)printf("%d, ", dp[i][j]);
//		printf("\n");
//	}

	printf("%d\n", dp[n][m]);

	return 0;
}
