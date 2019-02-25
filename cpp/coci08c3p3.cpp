//============================================================================
// Name        : coci08c3p3.cpp
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
 * - Anish Mahto, ?? - 37/75
 *
 * And many more... (sorry if I forgot you!)
 *
 * ~ M
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

int n,
	grid[9][9];
char buf[9];
bool blocked[10][9][9], blockedsq[10][3][3], available[3][3];

inline void blockval(int i, int j, int val){
	blockedsq[val][i / 3][j / 3] = true;

	for (int k = 0; k < 9; ++k) {
		blocked[val][i][k] = blocked[val][k][j] = true;
	}
}

inline bool run(){
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			int io = i * 3, jo = j * 3;

			for (int k = 1; k < 10; ++k) {
				if(blockedsq[k][i][j]) continue;
				memset(available, true, sizeof available);

				for (int l = 0; l < 3; ++l) {
					for (int m = 0; m < 3; ++m) {
						if(blocked[k][io + l][jo + m] || grid[io + l][jo + m] != -1)
							available[l][m] = false;
					}
				}

				int navailable = 0, lasti = -1, lastj = -1;
				for (int l = 0; l < 3; ++l) {
					for (int m = 0; m < 3; ++m) {
						if(available[l][m]){
							navailable++;
							lasti = l;
							lastj = m;
						}
					}
				}

				lasti += io;
				lastj += jo;

				if(navailable == 0)
					return false;
				else if(navailable == 1){
					grid[lasti][lastj] = k;
					blockval(lasti, lastj, k);
				}
			}
		}
	}

	return true;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	for (int i = 0; i < 9; ++i) {
		cin >> buf;

		for (int j = 0; j < 9; ++j) {
			if(buf[j] == '.')
				grid[i][j] = -1;
			else
				grid[i][j] = (int)(buf[j] - '0');
		}
	}

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			int val = grid[i][j];

			if(val != -1)
				blockval(i, j, val);
		}
	}

	for (int i = 0; i < 10; ++i) {
		bool ret = run();

		if(!ret){
			printf("ERROR\n");
			return 0;
		}
	}

	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			if(grid[i][j] != -1)
				printf("%d", grid[i][j]);
			else
				printf(".");
		}
		printf("\n");
	}
}
