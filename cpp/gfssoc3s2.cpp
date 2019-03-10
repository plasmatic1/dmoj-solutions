//============================================================================
// Name        : SokoBoop.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct p{
	int x, y, bx, by;
};

const int MAX = 31;
int r, c, sx, sy, bx, by, ex, ey,
	levels[MAX][MAX][MAX][MAX];
char grid[MAX][MAX];
deque<p> nxt;
p adjs[4];

inline void makeadjs(int x, int y, int bx, int by){
	// Right
	if(x + 1 == bx && y == by)
		adjs[0] = {x + 1, y, bx + 1, by};
	else
		adjs[0] = {x + 1, y, bx, by};

	// Left
	if(x - 1 == bx && y == by)
		adjs[1] = {x - 1, y, bx - 1, by};
	else
		adjs[1] = {x - 1, y, bx, by};

	// Up
	if(y + 1 == by && x == bx)
		adjs[2] = {x, y + 1, bx, by + 1};
	else
		adjs[2] = {x, y + 1, bx, by};

	// Down
	if(y - 1 == by && x == bx)
		adjs[3] = {x, y - 1, bx, by - 1};
	else
		adjs[3] = {x, y - 1, bx, by};
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> r >> c;

	for (int i = 0; i < r; ++i) {
		cin >> grid[i];
		for (int j = 0; j < c; ++j) {
			if(grid[i][j] == 'P')
				sx = i, sy = j;
			else if(grid[i][j] == 'B')
				bx = i, by = j;
			else if(grid[i][j] == 'X')
				ex = i, ey = j;
		}
	}

	memset(levels, -1, sizeof levels);
	levels[sx][sy][bx][by] = 0;
	nxt.push_back({sx, sy, bx, by});

	while(!nxt.empty()){
		p cur = nxt.front();
		nxt.pop_front();
		int level = levels[cur.x][cur.y][cur.bx][cur.by];

		makeadjs(cur.x, cur.y, cur.bx, cur.by);
		for(p adj : adjs){
			if(adj.x < 0 || adj.x >= r || adj.y < 0 || adj.y >= c || adj.bx < 0 || adj.bx >= r || adj.by < 0 || adj.by >= c ||
					grid[adj.x][adj.y] == '#' || grid[adj.bx][adj.by] == '#' || levels[adj.x][adj.y][adj.bx][adj.by] != -1)
				continue;

			levels[adj.x][adj.y][adj.bx][adj.by] = level + 1;
			nxt.push_back(adj);
		}
	}

	int best = INT_MAX;
	for (int i = 0; i < r; ++i)
		for (int j = 0; j < c; ++j)
			if(levels[i][j][ex][ey] != -1)
				best = min(best, levels[i][j][ex][ey]);

	if(best == INT_MAX) printf("-1\n");
	else printf("%d\n", best);
}