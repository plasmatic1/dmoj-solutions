//============================================================================
// Name        : ecoo19r1p3.cpp
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

int T =
#ifndef ONLINE_JUDGE
2
#else
10
#endif
;

const int MAXW = 101, MAXH = 11;
int j, w, h, sr, sc, er, ec,
	vis[MAXH][MAXW][3][11];
char grid[MAXH][MAXW];

int dfs(int r, int c, int jmpx, int jmpy) {
	if (r < 0 || r >= h || c < 0 || c >= w || grid[r][c] == '@') return -1;
	else if (r == er && c == ec) return 0x3f3f3f3f;
	int &ret = vis[r][c][jmpx][jmpy];
	if (ret != -1) return ret;

	if (jmpy)
		return ret = dfs(r - 1, c, jmpx, jmpy - 1);
	else if (jmpx)
		return ret = dfs(r, c + 1, jmpx - 1, jmpy);
	else if (grid[r + 1][c] != '#')
		return ret = dfs(r + 1, c, 0, 0);

	ret = max(c, dfs(r, c + 1, 0, 0));
	for (int i = 1; i <= j; i++)
		ret = max(ret, dfs(r, c, 2, i));
	return ret;
}

inline void solve() {
	int ans = dfs(sr, sc, 0, 0);
	if (ans >= 0x3f3f3f3f)
		printf("CLEAR\n");
	else
		printf("%d\n", ans + 2);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	while(T--) {
		scan(j, w, h);

		for (int i = 0; i < h; i++) {
			scan(grid[i]);
			for (int j = 0; j < w; j++) {
				if (grid[i][j] == 'L') {
					sr = i;
					sc = j;
					grid[i][j] = '.';
				}
				else if (grid[i][j] == 'G') {
					er = i;
					ec = j;
					grid[i][j] = '.';
				}
			}
		}

		memset(vis, -1, sizeof vis);
		solve();
	}

	return 0;
}
