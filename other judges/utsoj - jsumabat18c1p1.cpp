//============================================================================
// Name        : JsumabatContestP1.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 100001;
int n, k, ba, bb,
	levels[MAX];
vector<int> matrix[MAX];

inline void bfs(int *lvl, int start){
	lvl[start] = 0;
	deque<int> nextt;
	nextt.push_back(start);

	while(!nextt.empty()){
		int curr = nextt.front(), lv = lvl[curr];
		nextt.pop_front();

		for(int adj : matrix[curr]){
			if(lvl[adj] == -1){
				lvl[adj] = lv + 1;
				nextt.push_back(adj);
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;

	for (int i = 1; i < n; ++i) {
		cin >> ba >> bb;

		matrix[ba].emplace_back(bb);
		matrix[bb].emplace_back(ba);
	}

	memset(levels, -1, sizeof(levels));
	bfs(levels, 1);

	int bestv = -1, besti = -1;
	for(int i = 1; i <= n; i++){
		if(levels[i] > bestv){
			bestv = levels[i];
			besti = i;
		}
	}

	memset(levels, -1, sizeof(levels));
	bfs(levels, besti);

	int maxv = *max_element(levels + 1, levels + 1 + n);

	if(maxv < k){
		printf("Graph Theory!\n");
	}
	else{
		printf("NO U");
	}
}
