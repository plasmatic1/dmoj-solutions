//============================================================================
// Name        : Waterpark.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 10000;
int n, ba = 1, bb = 1,
		dp[MAX];
vector<int> matrix[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	while(ba != 0 && bb != 0){
		cin >> ba >> bb;

		matrix[ba].push_back(bb);
	}

	dp[1] = 1;
	for (int i = 1; i < n; ++i) {
		for(int adj : matrix[i]){
			dp[adj] += dp[i];
		}
	}

	printf("%d\n", dp[n]);
}
