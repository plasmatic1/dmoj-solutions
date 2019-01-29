//============================================================================
// Name        : InterNAV.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct co{
	int x, y;

	co() : x(-1), y(-1){}
	co(int x0, int y0) : x(x0), y(y0){}
};

const int MAX = 1000;
int n, m;

char grid[MAX][MAX];

deque<co> nextt;
//int levels[MAX][MAX];
bool vis[MAX][MAX];

co adjcs[4];

inline void genadjs(co &v){
	adjcs[0] = co(v.x + 1, v.y);
	adjcs[1] = co(v.x - 1, v.y);
	adjcs[2] = co(v.x, v.y + 1);
	adjcs[3] = co(v.x, v.y - 1);
}

inline bool inbounds(co &v){
	return v.x >= 0 && v.y >= 0 && v.x < m && v.y < n;
}

set<int> work;
co start;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m;

	for (int i = 0; i < m; ++i) {
		cin >> grid[i];

		for (int j = 0; j < n; ++j) {
			if(grid[i][j] == '1'){
				start = co(i, j);
			}
		}
	}

	work.insert(1);

	vis[start.x][start.y] = true;
	nextt.push_back(start);

	while(!nextt.empty()){
		co curr = nextt.front();
		nextt.pop_front();

		genadjs(curr);
//		printf("on co %d %d\n", curr.x, curr.y);
//		assert(recc--);

		for(co adj : adjcs){
			if(!inbounds(adj) || vis[adj.x][adj.y]){
				continue;
			}

			if(grid[adj.x][adj.y] == '#'){
				continue;
			}

			if(grid[adj.x][adj.y] != 'O'){
				work.insert((int)(grid[adj.x][adj.y] - '0'));
			}

			nextt.push_back(adj);
			vis[adj.x][adj.y] = true;
		}
	}

	for(int x : work){
		printf("%d ", x);
	}
	printf("\n");
}
