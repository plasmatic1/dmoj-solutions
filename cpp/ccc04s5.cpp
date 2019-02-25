//============================================================================
// Name        : ccc04s5.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

/*
 * Dear Reader,
 *
 * I'm writing this in response to CCC 2019.  Despite all the training I had gone through and high hopes and
 * encouragement from friends I tied with many others for a dismal score of 33.
 * Obviously, setting a cutoff that low would mean much too many people making CCO.
 *
 * I was excluded.
 *
 * After that, I developed depression.  I lost my will to do anything in life.
 *
 * Despite having worked so hard, I ended up choking at the worst possible time- right in the middle of the
 * CCC.  My heart goes out to everyone else who has or will suffer from the same fate.  To whom it may concern,
 * yes, I'm talking to you
 *
 * Moral of the story: If you train hard and practice well, but choke on the CCC and not make CCO, then your
 * hard work was just for nothing.
 *
 * ...
 *
 * What happens next is for you to decide
 *
 *  Read this if you want to feel better: https://dmoj.ca/problem/tle17c7p3/editorial
 *
 * ------------------------------------------------------------------------------------------------
 *
 * == vector<string> of Lost Souls: ==
 *
 * - Andrew Qi Tang, Erindale SS - 37/75
 * - Zeyu Chen, Colonel By SS - 37/75
 * - Andrew ? (not sure about last name), ?? - 36/75
 * - Aaron Tang, Churchill Heights PS - 37/75
 * - David Tsukernik, Stephen Lewis SS - 30/75
 * - Jonathan Sumabat, Thornhill SS - 27/75 (or was it 30?)
 * - Leon Dong, Bayview SS - 34/75
 * - Eric Pei, Don Mills CI - 41/75
 * -
 *
 * And many more... (sorry if I forgot you!)
 *
 * ~ M
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 101, INF = 0x3f3f3f3f;
int n, m,
	grid[MAX][MAX], vis[2][2][MAX][MAX];
char buf[MAX];

int rec(int r, int c, bool lastup, bool lastdown){
	if(r < 0 || r >= n || c < 0 || c >= m || grid[r][c] == -1) return -INF;
	if(r == n - 1 && c == m - 1) return grid[r][c];
	int &ret = vis[lastup][lastdown][r][c];
	if(ret != -1) return ret;

	ret = -INF;
	if(!lastdown) // Can go up
		ret = rec(r - 1, c, true, false);
	if(!lastup) // Can go down
		ret = max(ret, rec(r + 1, c, false, true));
	ret = max(ret, rec(r, c + 1, false, false));

	return ret += grid[r][c];
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	while(n && m){
		for (int i = 0; i < n; ++i) {
			cin >> buf;

			for (int j = 0; j < m; ++j) {
				if(buf[j] == '.')
					grid[i][j] = 0;
				else if(buf[j] == '*')
					grid[i][j] = -1;
				else
					grid[i][j] = (int)(buf[j] - '0');
			}
		}

		memset(vis, -1, sizeof vis);
		printf("%d\n", rec(n - 1, 0, false, false));

		cin >> n >> m;
	}
}
