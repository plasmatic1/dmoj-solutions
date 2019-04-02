//============================================================================
// Name        : coci08c4p4.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

/*
 * States
 * 0 -> Black
 * 1 -> White
 * 2 -> Undecided
 */
const int MAX = 512 + 1, INF = 0x3f3f3f3f, ARRANGEMENTS[12][4] = {
		{2, 2, 0, 1},
		{2, 2, 1, 0},
		{2, 0, 2, 1},
		{2, 1, 2, 0},
		{2, 0, 1, 2},
		{2, 1, 0, 2},
		{0, 2, 2, 1},
		{1, 2, 2, 0},
		{0, 2, 1, 2},
		{1, 2, 0, 2},
		{0, 1, 2, 2},
		{1, 0, 2, 2}
};
int n,
	ranks[MAX]; // compression for cbest array
char bs[MAX];
bool grid[MAX][MAX], best[10][MAX][MAX];

inline int whiteCnt(int x, int x2, int y, int y2){
	int tot = 0;
	for(int i = x; i < x2; i++)
		for(int j = y; j < y2; j++)
			tot += grid[i][j];
	return tot;
}

// Gets the difference of an area based on state, curr, currWhite, and currSize
inline int difference(int state, int curr, int white, int area){
	switch(state){
	case 0: return white;
	case 1: return area - white;
	}
	return curr; // state == 2
}

inline void apply(int state, int x, int x2, int y, int y2){
	if(state < 2){
		int crank = ranks[x2 - x] + 1; // Add 1 since we know this is applying colours on a subsquare
		for(int i = x; i < x2; i++)
			for(int j = y; j < y2; j++)
				best[crank][i][j] = state;
	}
	else{
		int crank = ranks[x2 - x];
		for(int i = x; i < x2; i++)
			for(int j = y; j < y2; j++)
				best[crank + 1][i][j] = best[crank][i][j];
	}
}

int rec(int x, int x2, int y, int y2){
	if(x + 1 == x2){
		best[0][x][y] = grid[x][y];
		return 0;
	}

	int midx = (x + x2) >> 1, midy = (y + y2) >> 1, bestv = 0x3f3f3f3f, besti = -1, area = (midx - x) * (midx - x),
		topl = rec(x, midx, y, midy), topr = rec(x, midx, midy, y2), botl = rec(midx, x2, y, midy), botr = rec(midx, x2, midy, y2),
		toplWhite = whiteCnt(x, midx, y, midy), toprWhite = whiteCnt(x, midx, midy, y2), botlWhite = whiteCnt(midx, x2, y, midy), botrWhite = whiteCnt(midx, x2, midy, y2);

	for (int i = 0; i < 12; ++i) {
		int cur = difference(ARRANGEMENTS[i][0], topl, toplWhite, area) + difference(ARRANGEMENTS[i][1], topr, toprWhite, area) +
				difference(ARRANGEMENTS[i][2], botl, botlWhite, area) + difference(ARRANGEMENTS[i][3], botr, botrWhite, area);

		if(cur < bestv){
			bestv = cur;
			besti = i;
		}
	}

	apply(ARRANGEMENTS[besti][0], x, midx, y, midy);
	apply(ARRANGEMENTS[besti][1], x, midx, midy, y2);
	apply(ARRANGEMENTS[besti][2], midx, x2, y, midy);
	apply(ARRANGEMENTS[besti][3], midx, x2, midy, y2);

	return bestv;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> bs;

		for (int j = 0; j < n; ++j)
			grid[i][j] = bs[j] == '1';
	}

	for(int i = 1, ctr = 0; i <= 512; i <<= 1, ctr++)
		ranks[i] = ctr;

	// Output
	printf("%d\n", rec(0, n, 0, n));

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			printf("%d", best[ranks[n]][i][j]);
		printf("\n");
	}
}
