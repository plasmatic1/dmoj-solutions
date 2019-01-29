//============================================================================
// Name        : Errands.cpp
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
int n, m, q, c, ba, bb,
	levels[MAX];
vector<int> matrix[MAX];
deque<int> nextt;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> q >> c;

	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb;

		matrix[ba].push_back(bb);
		matrix[bb].push_back(ba);
	}

	// BFS

	memset(levels, -1, sizeof(levels));

	levels[c] = 0;
	nextt.push_back(c);

	while(!nextt.empty()){
		int curr = nextt.front(), level = levels[curr];
		nextt.pop_front();

		for(int adj : matrix[curr]){
			if(levels[adj] == -1){
				levels[adj] = level + 1;
				nextt.push_back(adj);
			}
		}
	}

	// Queries

	for (int i = 0; i < q; ++i) {
		cin >> ba >> bb;

		if(levels[ba] == -1 || levels[bb] == -1){
			printf("This is a scam!\n");
		}
		else{
			printf("%d\n", levels[ba] + levels[bb]);
		}
	}
}
