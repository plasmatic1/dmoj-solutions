//============================================================================
// Name        : YouCantWriteScienceFictionBetterThanThis.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

int n, m, a, b, ba, bb;
const int MAX = 1001;

vector<int> matrix[MAX];
int levels[MAX], levels2[MAX];
deque<int> nextt;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> a >> b;

	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb;

		matrix[ba].push_back(bb);
		matrix[bb].push_back(ba);
	}

	//bfs

	fill(levels, levels + n + 1, -1);
	levels[1] = 0;
	nextt.push_back(1);

	while(!nextt.empty()){
		int curr = nextt.front(), level = levels[curr];
		nextt.pop_front();

		for(int adj : matrix[curr]){
			if(levels[adj] != -1){
				continue;
			}

			levels[adj] = level + 1;
			nextt.push_back(adj);
		}
	}

	if(levels[a] == -1){
		printf("%d\n", -1);
		return 0;
	}

	//bfs 2
	fill(levels2, levels2 + n + 1, -1);
	levels2[a] = 0;
	nextt.push_back(a);

	while(!nextt.empty()){
		int curr = nextt.front(), level = levels2[curr];
		nextt.pop_front();

		for(int adj : matrix[curr]){
			if(levels2[adj] != -1){
				continue;
			}

			levels2[adj] = level + 1;
			nextt.push_back(adj);
		}
	}

//	printf("levels: ");
//	for (int i = 0; i < n + 1; ++i) {
//		printf("%d, ", levels[i]);
//	}
//	printf("\n");
//	printf("levels2: ");
//	for (int i = 0; i < n + 1; ++i) {
//		printf("%d, ", levels2[i]);
//	}
//	printf("\n");
//	printf("%d %d\n", a, b);


	if(levels2[b] == -1){
		printf("%d\n", -1);
	}
	else{
		printf("%d\n", levels[a] + levels2[b]);
	}
}
