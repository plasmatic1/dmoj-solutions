//============================================================================
// Name        : tree2.cpp
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
	int x, y, w, cnt;

	bool operator<(const p &o) const {
		if (w == o.w)
			return cnt > o.cnt;
		return w > o.w;
	}
};

struct pco {
	int x, y;
};

const int MAX = 11;
int n, m, sx, sy, bestX, bestY, bestHeight = -1, bestTDis = 0x3f3f3f3f,
	grid[MAX][MAX], dis[MAX][MAX], cnt[MAX][MAX];
char buf;
priority_queue<p> nxt;
pco adjs[4];

inline void makeAdjs(const p pos) {
	adjs[0] = {pos.x + 1, pos.y};
	adjs[1] = {pos.x - 1, pos.y};
	adjs[2] = {pos.x, pos.y + 1};
	adjs[3] = {pos.x, pos.y - 1};
}

inline int disSquared(int x, int y, int x2, int y2) {
	int dx = x - x2, dy = y - y2;
	return dx * dx + dy * dy;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	scan(n, m);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scan(buf);

			if (buf == 'X') {
				sx = i;
				sy = j;
			}
			else if (buf == '.')
				continue;
			else
				grid[i][j] = buf - '0';
		}
	}

	memset(dis, 0x3f, sizeof dis);
	dis[sx][sy] = cnt[sx][sy] = 0;
	nxt.push({sx, sy, 0, 0});

	while (!nxt.empty()) {
		p cur = nxt.top();
		nxt.pop();

		if (cur.w > dis[cur.x][cur.y])
			continue;

		makeAdjs(cur);
		for (pco adj : adjs) {
			if (adj.x < 0 || adj.x >= n || adj.y < 0 || adj.y >= m)
				continue;

			int alt = cur.w + grid[adj.x][adj.y], &adjDis = dis[adj.x][adj.y], &adjCnt = cnt[adj.x][adj.y],
					altCnt = cur.cnt + (grid[adj.x][adj.y] != 0);
			if (alt < adjDis || (alt == adjDis && altCnt < adjCnt)) {
				adjDis = alt;
				adjCnt = altCnt;
				nxt.push({adj.x, adj.y, alt, altCnt});
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] > bestHeight || (grid[i][j] == bestHeight &&
					disSquared(sx, i, sy, j) < bestTDis)) {
				bestHeight = grid[i][j];
				bestX = i;
				bestY = j;
				bestTDis = disSquared(sx, i, sy, j);
			}
		}
	}

	printf("%d\n", cnt[bestX][bestY] - 1);
}