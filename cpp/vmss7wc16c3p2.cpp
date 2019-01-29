//============================================================================
// Name        : CanShahirEvenGetThere.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 2001;
int n, m, a, b,
	ba, bb;

int levels[MAX];
vector<int> matrix[MAX];

void dfs(int curr, int level){
	levels[curr] = level;

	for(int adj : matrix[curr]){
		if(levels[adj] == -1){
			dfs(adj, level + 1);
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> a >> b;
	fill(levels, levels + n + 1, -1);

	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb;

		matrix[ba].push_back(bb);
		matrix[bb].push_back(ba);
	}

	dfs(a, 0);

	if(levels[b] != -1){
		printf("GO SHAHIR!");
	}
	else{
		printf("NO SHAHIR!");
	}
}
