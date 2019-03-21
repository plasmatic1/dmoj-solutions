//============================================================================
// Name        : usaco19febbronze1.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 110;
int n, m, ba, bb,
	dp[MAX];
vector<int> matrix[MAX];

int main(){
	freopen("revegetate.in", "r", stdin);
	freopen("revegetate.out", "w", stdout);

	cin >> n >> m;

	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb;
		matrix[max(ba, bb)].push_back(min(ba, bb));
	}

	for (int i = 1; i <= n; ++i)
		sort(matrix[i].begin(), matrix[i].end());

	fill(dp + 1, dp + n + 1, 1);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= 4; j++){
			bool pass = true;

			for(int adj : matrix[i]){
				if(dp[adj] == j){
					pass = false;
					break;
				}
			}

			if(pass){
				dp[i] = j;
				break;
			}
		}
	}

	// check
	for(int i = 1; i <= n; i++){
		assert(dp[i] <= 4);
		for(int adj : matrix[i])
			assert(dp[i] != dp[adj]);
	}

	for (int i = 1; i <= n; ++i)
		printf("%d", dp[i]);
	printf("\n");
}
