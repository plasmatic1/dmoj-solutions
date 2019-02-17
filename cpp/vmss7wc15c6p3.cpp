//============================================================================
// Name        : vmss7wc15c6p3.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 400001;
int n, ba, bb, best = INT_MIN,
	vals[MAX];
vector<int> matrix[MAX];

int dfs(int cur){
	for(int adj : matrix[cur])
		vals[cur] += dfs(adj);
	best = max(best, vals[cur]);
	return vals[cur];
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;

	for(int i = 1; i < n; i++){
		cin >> ba >> bb;
		matrix[ba].push_back(bb);
	}

	for(int i = 1; i <= n; i++)
		cin >> vals[i];

	dfs(1);

	printf("%d\n", best);
}