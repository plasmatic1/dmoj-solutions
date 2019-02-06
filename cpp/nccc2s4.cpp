//============================================================================
// Name        : nccc2s4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAX = 50001;
int n, ba, bb, bc;
vector<int> goods,
	bads[MAX];
bool bad[MAX];
unordered_map<int, vector<int>> matrix[MAX];

void dfs(int cur, int par, int parclr){
	for(auto adjs : matrix[cur]){
		int w = adjs.first;

		for(int adj : adjs.second){
			if(adj ^ par){
				dfs(adj, cur, w);
				if(bad[adj]) bads[cur].push_back(adj);
			}
		}
	}

	bad[cur] = (!bads[cur].empty()) || (matrix[cur][parclr].size() > 1);
}

void dfs2(int cur, int par, int parclr){
	if(bads[cur].size() > 1) return;
	// If the node has at least 2 bad subtrees, there's no point in checking the
	// children because any path coming from the children has to go into another one of
	// the children

	for(auto adjs : matrix[cur]){
		int w = adjs.first;

		if(adjs.second.size() > 1) continue;
		for(int adj : adjs.second){
			if(par ^ adj){
				if(bads[cur].empty() || bads[cur][0] == adj)
					dfs2(adj, cur, w);
			}
		}
	}

	if(bads[cur].empty()) goods.push_back(cur);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;

	for(int i = 1; i < n; i++){
		cin >> ba >> bb >> bc;

		matrix[ba][bc].push_back(bb);
		matrix[bb][bc].push_back(ba);
	}

	dfs(1, -1, -1);
	dfs2(1, -1, -1);

	printf("%u\n", goods.size());
	sort(goods.begin(), goods.end());
	for(int i : goods) printf("%d\n", i);

	return 0;
}