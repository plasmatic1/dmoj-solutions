//============================================================================
// Name        : cco96p6.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Scan and Debug
void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F f, R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

struct p {
	int r, c, vr, vc;
};

const int MAX = 16 + 1, DIRS[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
int r, c, sr, sc, er, ec,
	levels[MAX][MAX][7][7];
char grid[MAX][MAX];
p adjs[9];
queue<p> nxt;

#define get(x, y, vx, vy) levels[x][y][(vx) + 3][(vy) + 3]

void makeAdjs(p &cur) {
	int ptr = -1;
	for (int i = -1; i <= 1; ++i)
		for (int j = -1; j <= 1; ++j)
			adjs[++ptr] = {cur.r + cur.vr + i, cur.c + cur.vc + j, cur.vr + i, cur.vc + j};
}

void solve() {
	nxt.push({sr, sc, 0, 0});
	get(sr, sc, 0, 0) = 0;

	while (!nxt.empty()) {
		p cur = nxt.front(); nxt.pop();
		int level = get(cur.r, cur.c, cur.vr, cur.vc);

		makeAdjs(cur);
		for (p adj : adjs) {
			if (adj.r < 0 || adj.r >= r || adj.c < 0 || adj.c >= c || adj.vr < -3 || adj.vr > 3 ||
					adj.vc < -3 || adj.vc > 3 || grid[adj.r][adj.c] == '#' ||
					get(adj.r, adj.c, adj.vr, adj.vc) != -1)
				continue;

			nxt.push(adj);
			get(adj.r, adj.c, adj.vr, adj.vc) = level + 1;
		}
	}

	int best = 0x3f3f3f3f;
	for (int i = -3; i <= 3; i++)
		for (int j = -3; j <= 3; j++)
			if (get(er, ec, i, j) != -1)
				best = min(best, get(er, ec, i, j));

	if (best == 0x3f3f3f3f)
		cout << "No solution.\n";
	else
		cout << "Optimal solution takes " << best << " hops.\n";
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int t; scan(t);
	while (t--) {
		int n, bc1, bc2, br1, br2;
		scan(c, r, sc, sr, ec, er, n);

		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c; ++j)
				grid[i][j] = '.';

		for (int i = 0; i < n; ++i) {
			scan(bc1, bc2, br1, br2);
			for (int j = br1; j <= br2; ++j)
				for (int k = bc1; k <= bc2; ++k)
					grid[j][k] = '#';
		}

		memset(levels, -1, sizeof levels);
		solve();
	}
}