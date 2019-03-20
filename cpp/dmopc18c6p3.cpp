//============================================================================
// Name        : dmopc18c6p2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 200001;
int n, m, ba, bb,
	collisions = 0;
vector<int> matrix[MAX];
bool vis[MAX];

void dfs(int cur, int par){
	if(vis[cur]){
//		printf("at cur=%d collisions=%d\n", cur, collisions);
		collisions++;
		return;
	}

//	printf("cur=%d\n", cur);

	vis[cur] = true;

	for(int adj : matrix[cur])
		if(adj ^ par)
			dfs(adj, cur);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m;

	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb;
		matrix[ba].push_back(bb);
		matrix[bb].push_back(ba);
	}

	for(int i = 1; i <= n; i++)
		if(!vis[i])
			dfs(i, -1);

	if(collisions <= 2)
		printf("YES\n");
	else
		printf("NO\n");
}