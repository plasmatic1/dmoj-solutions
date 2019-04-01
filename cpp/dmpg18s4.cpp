//============================================================================
// Name        : dmpg18s4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const int MAX = 200001;
int n, ba, bb,
	parity[MAX];
ll dp[MAX];
vector<int> matrix[MAX];

ll dfs(int cur, int par){
	dp[cur] += parity[cur];

	for(int adj : matrix[cur]){
		if(adj ^ par){
			ll ret = dfs(adj, cur);
			if(parity[adj] ^ parity[cur])
				dp[cur] += ret;
		}
	}

	return dp[cur];
}

void dfs2(int cur, int par){
	if(par != -1){
		if(parity[par] != parity[cur])
			dp[cur] += dp[par] - dp[cur];
	}

	for (int adj : matrix[cur]){
		if(adj ^ par)
			dfs2(adj, cur);
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;

	for (int i = 1; i <= n; i++){
		cin >> parity[i];
		parity[i] &= 1;
	}

	for (int i = 1; i < n; i++){
		cin >> ba >> bb;
		matrix[ba].push_back(bb);
		matrix[bb].push_back(ba);
	}

	dfs(1, -1);
	dfs2(1, -1);

	ll ans = 0;
	for (int i = 1; i <= n; i++)
		ans += dp[i];
	printf("%lld\n", ans);
}
