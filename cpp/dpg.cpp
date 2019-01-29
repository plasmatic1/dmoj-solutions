//============================================================================
// Name        : AtcoderDpG.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 100001;
int n, m, ba, bb, best = -1,
	dp[MAX], idx[MAX];
vector<int> topo,
	matrix[MAX], amatrix[MAX];
bool vis[MAX];

void tsort(int cur){ // Topological Sort
	vis[cur] = true;
	for(int adj : amatrix[cur])
		if(!vis[adj]) tsort(adj);
	topo.push_back(cur);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb;

		matrix[ba].push_back(bb);
		amatrix[bb].push_back(ba);
	}

	for(int i = 1; i <= n; i++)
		if((int)matrix[i].size() == 0) tsort(i);

	for (int i = 0; i < n; ++i) {
		idx[topo[i]] = i;
	}

	for(int i = 0; i < n; i++){
		for(int adj : matrix[topo[i]])
			dp[idx[adj]] = max(dp[idx[adj]], dp[i] + 1);
		best = max(best, dp[i]);
	}

	printf("%d\n", best);
}
