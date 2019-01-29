//============================================================================
// Name        : GeeseVsHawks.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 1001;
int n, m, buf,
	geesepts[MAX], hawkpts[MAX], dp[MAX][MAX];

bool pass(int i, int j){
	return geesepts[i] == hawkpts[j];
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	//Input

	cin >> n >> m;

	for (int i = 1; i <= n; ++i) {
		cin >> geesepts[i];
	}

	for (int i = 1; i <= m; ++i) {
		cin >> hawkpts[i];
	}

	//Dp

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			dp[i][j] = max(dp[i - 1][j], max(dp[i][j - 1], dp[i - 1][j - 1] + pass(i, j)));
		}
	}

	printf("%d\n", dp[n][m]);
}
