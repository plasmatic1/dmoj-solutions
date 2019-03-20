//============================================================================
// Name        : dmopc18c6p0.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 10;
int n, ba;
vector<int> matrix[MAX];
bool ret = false,
	vis[MAX];

bool dfs(int cur){
	if(vis[cur]) return true;
	vis[cur] = true;

	for(int adj : matrix[cur]){
		if(dfs(adj)) return true;
	}

	return false;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	for(int i = 1; i <= 3; i++){
		cin >> ba;
		matrix[i].push_back(ba);
	}

	for(int i = 1; i <= 3; i++){
		memset(vis, false, sizeof vis);
		ret |= dfs(i);
	}

	if(ret) printf("NO\n");
	else printf("YES\n");
}