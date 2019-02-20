//============================================================================
// Name        : dpp.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const ll MOD = 1000000007;
const int MAX = 100001;
int n, ba, bb;
ll dp[2][MAX];
vector<int> matrix[MAX];

void dfs(int cur, int par){
	ll whiteProd = 1, blackProd = 1;

	for(int adj : matrix[cur]){
		if(adj ^ par){
			dfs(adj, cur);

			whiteProd = (whiteProd * ((dp[0][adj] + dp[1][adj]) % MOD)) % MOD;
			blackProd = (blackProd * dp[1][adj]) % MOD;
		}
	}

	if(!matrix[cur].size())
		dp[0][cur] = dp[1][cur] = 1;
	else{
		dp[0][cur] = blackProd;
		dp[1][cur] = whiteProd;
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for(int i = 1; i < n; i++){
		cin >> ba >> bb;

		matrix[ba].push_back(bb);
		matrix[bb].push_back(ba);
	}

	dfs(1, -1);
	printf("%lld\n", (dp[0][1] + dp[1][1]) % MOD);
}
