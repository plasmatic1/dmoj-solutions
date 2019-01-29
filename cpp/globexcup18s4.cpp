//============================================================================
// Name        : ReverseDijkstras.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 19;
int n, m, a, b, v, ba, bb, best = 0x3f3f3f3f, bestlen = 0x3f3f3f3f;

vector<int> matrix[MAX];

void dfs(int curr, int mask, int dis){
	if(best == 0){
		return;
	}

	if(curr == b){
		int curramt = abs(v - dis);

		if(curramt < best){
			best = curramt;
			bestlen = dis;
		}
		else if(curramt == best){
			bestlen = min(bestlen, dis);
		}

		return;
	}

//	printf("curr=%d dis=%d\n", curr, dis);

	for(int adj : matrix[curr]){
		int nodemask = 1 << adj;

		if(!(mask & nodemask)){
			dfs(adj, mask | nodemask, dis + 1);
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> a >> b >> v;

	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb;

		matrix[ba].push_back(bb);
		matrix[bb].push_back(ba);
	}

	dfs(a, 1 << a, 0);

	printf("%d\n", bestlen);
}
