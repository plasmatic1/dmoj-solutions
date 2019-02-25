//============================================================================
// Name        : dmopc17c2p3.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 200001;
int n, r, x, y, ba, bb, minv = INT_MAX,
	levels[MAX];
vector<int> matrix[MAX];
deque<int> nxt;

bool dfs(int cur, int par){
	if(cur == y){
		minv = min(minv, levels[y]);
		return true;
	}

	bool flag = false;

	for(int adj : matrix[cur]){
		if(adj ^ par)
			flag |= dfs(adj, cur);
	}

	if(flag)
		minv = min(minv, levels[cur]);

	return flag;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> r;

	for(int i = 1; i < n; i++){
		cin >> ba >> bb;
		matrix[ba].push_back(bb);
		matrix[bb].push_back(ba);
	}

	memset(levels, -1, sizeof levels);
	for(int i = 0; i < r; i++){
		cin >> ba;
		levels[ba] = 0;
		nxt.push_back(ba);
	}

	cin >> x >> y;

	while(!nxt.empty()){
		int cur = nxt.front(), lvl = levels[cur];
		nxt.pop_front();

		for(int adj : matrix[cur]){
			if(levels[adj] == -1){
				levels[adj] = lvl + 1;
				nxt.push_back(adj);
			}
		}
	}

	dfs(x, -1);

	printf("%d\n", minv);
}
