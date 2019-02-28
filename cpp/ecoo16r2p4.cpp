//============================================================================
// Name        : ecoo16r2p4.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct p{
	int x, y;
};

const int T =
#ifndef ONLINE_JUDGE
1;
#else
10;
#endif

const int MAX = 210, MA = 41;
int w, h, hopx, hopy, skipx, skipy, jumpx, jumpy;
char grid[MAX][MAX];
bool vis[MAX][MAX];
p adjs[MA];
string buf;

inline bool isempty(int x, int y){
	switch(grid[x][y]){
	case 'C':
	case 'F':
	case 'T':
	case '.':
	return true;
	}
	return false;
}

// Makes adjecents and returns the size (since it's variable)
inline int makeadjs(int x, int y, char type){
	int sz = 0;

	// Falling forever
	if(y == 0 && isempty(x, y)) return 0;

	// If falling
	if(y - 1 >= 0 && grid[x][y] != '#' && grid[x][y - 1] != '=' && grid[x][y - 1] != '#'){
		adjs[sz++] = {x, y - 1};
		return 1;
	}

	// Left (All)
	if(x - 1 >= 0 && grid[x - 1][y] != '=')
		adjs[sz++] = {x - 1, y};

	// Right (All)
	if(x + 1 < w && grid[x + 1][y] != '=')
		adjs[sz++] = {x + 1, y};

	// Up (Ladder)
	if(y + 1 < h && grid[x][y] == '#' && grid[x][y + 1] != '=')
		adjs[sz++] = {x, y + 1};

	// Down (Ladder)
	if(y - 1 >= 0 && grid[x][y - 1] == '#')
		adjs[sz++] = {x, y - 1};

	// Hop
	if(type == 'h' || type == 'j'){
		// left hop
		if(x - 1 >= 0 && y + 1 < h && grid[x][y + 1] != '=' && grid[x - 1][y + 1] != '=')
			adjs[sz++] = {x - 1, y + 1};

		// right hop
		if(x + 1 < w && y + 1 < h && grid[x][y + 1] != '=' && grid[x + 1][y + 1] != '=')
			adjs[sz++] = {x + 1, y + 1};

		// up hop
		if(y + 1 < h && grid[x][y + 1] != '=')
			adjs[sz++] = {x, y + 1};
	}
	if(type == 's' || type == 'j'){
		// left skip
		if(x - 2 >= 0 && grid[x - 1][y] != '=' && grid[x - 2][y] != '=')
			adjs[sz++] = {x - 2, y};

		// right skip
		if(x + 2 < w && grid[x + 1][y] != '=' && grid[x + 2][y] != '=')
			adjs[sz++] = {x + 2, y};
	}
	if(type == 'j'){ // jump
		// left jump
		if(x - 3 >= 0 && grid[x - 1][y] != '=' && grid[x - 2][y] != '=' && grid[x - 3][y] != '=')
			adjs[sz++] = {x - 3, y};

		// right jump
		if(x + 3 < w && grid[x + 1][y] != '=' && grid[x + 2][y] != '=' && grid[x + 3][y] != '=')
			adjs[sz++] = {x + 3, y};

		// left high jump
		if(x - 2 >= 0 && y + 1 < h && grid[x - 1][y] != '=' && grid[x][y + 1] != '=' && grid[x - 1][y + 1] != '=' && grid[x - 2][y + 1] != '=')
			adjs[sz++] = {x - 2, y + 1};

		// right high jump
		if(x + 2 < w && y + 1 < h && grid[x + 1][y] != '=' && grid[x][y + 1] != '=' && grid[x + 1][y + 1] != '=' && grid[x + 2][y + 1] != '=')
			adjs[sz++] = {x + 2, y + 1};

		// spring jump
		if(y + 2 < h && grid[x][y + 1] != '=' && grid[x][y + 2] != '=')
			adjs[sz++] = {x, y + 2};
	}

	return sz;
}

inline void bfs(int x, int y, char type, vector<char> &ret){
	memset(vis, false, sizeof vis);
	deque<p> nxt;

	vis[x][y] = true;
	nxt.push_back({x, y});

	while(!nxt.empty()){
		p cur = nxt.front();
		nxt.pop_front();

		int sz = makeadjs(cur.x, cur.y, type);

		for (int i = 0; i < sz; ++i) {
			p adj = adjs[i];

			if(!vis[adj.x][adj.y]){
				vis[adj.x][adj.y] = true;

				switch(grid[adj.x][adj.y]){
				case 'C':
				case 'F':
				case 'T':
				ret.push_back(grid[adj.x][adj.y]);
				}

				nxt.push_back(adj);
			}
		}
	}

	sort(ret.begin(), ret.end());
}

void printv(string label, vector<char> &vec){
	if(vec.empty())
		printf("%s\n", label.c_str());
	else{
		printf("%s ", label.c_str());
		for(char c : vec) printf("%c", c);
		printf("\n");
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	for (int asidufhisdufhasuifhaisuhf = 0; asidufhisdufhasuifhaisuhf < T; ++asidufhisdufhasuifhaisuhf) {
		cin >> w >> h;

		for(int i = 0; i < h; i++){
			cin >> buf;
			for(int j = 0; j < w; j++){
				int y = h - i - 1;
				if(buf[j] == 'h')
					hopx = j, hopy = y, grid[j][y] = '.';
				else if(buf[j] == 's')
					skipx = j, skipy = y, grid[j][y] = '.';
				else if(buf[j] == 'j')
					jumpx = j, jumpy = y, grid[j][y] = '.';
				else
					grid[j][y] = buf[j];
			}
		}

		vector<char> hret, sret, jret;

		bfs(hopx, hopy, 'h', hret);
		bfs(skipx, skipy, 's', sret);
		bfs(jumpx, jumpy, 'j', jret);

		printv("HOP", hret);
		printv("SKIP", sret);
		printv("JUMP", jret);
	}
}
