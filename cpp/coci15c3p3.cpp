//============================================================================
// Name        : coci15c3p3.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct p{
	int a, b;
};

const int MAX = 100010;
int n, ba, bb;
bool parity[MAX]; // 0 -> Inwards, 1 -> Outwards
vector<int> matrix[MAX];
p edges[MAX];

void dfs(int cur, int par){
	parity[cur] = !parity[par];

	for(int adj : matrix[cur])
		if(adj ^ par)
			dfs(adj, cur);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;

	for(int i = 1; i < n; i++){
		cin >> ba >> bb;
		matrix[ba].push_back(bb);
		matrix[bb].push_back(ba);
		edges[i] = {ba, bb};
	}

	dfs(1, n + 1);

	for(int i = 1; i < n; i++)
		printf("%d\n", parity[edges[i].a] == 1 && parity[edges[i].b] == 0);
}