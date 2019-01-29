//============================================================================
// Name        : Stol.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
//#define DEBUG

using namespace std;

const int MAX = 400;

typedef long long ll;
typedef pair<int, int> p;

int r, c, dp[MAX][MAX], lft[MAX], rht[MAX];
char lineb[MAX][MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> r >> c;

	for (int i = 0; i < r; ++i) {
		cin >> lineb[i];
	}

	memset(dp, 0, sizeof(dp));

	for (int i = 0; i < r; ++i) {
		int curr = 0;

		for (int j = 0; j < c; ++j) {
			curr = lineb[i][j] == '.' ? curr + 1 : 0;
			dp[i][j] = curr;
		}
	}

	int maxx = 0;

	for (int i = 0; i < c; ++i) {
		deque<p> deq;
		fill(lft, lft + r, -1);
		fill(rht, rht + r, r);

		deq.push_back(p(0, INT_MIN));

		for (int j = 0; j < r; ++j) {
			int val = dp[j][i];

			while(val < deq.back().second){
				p last = deq.back();

				deq.pop_back();

				lft[last.first - 1] = deq.back().first - 1;
				rht[last.first - 1] = j;
			}

			deq.push_back(p(j + 1, val));
		}

		while(deq.size() > 1){
			p last = deq.back();

			deq.pop_back();
			lft[last.first - 1] = deq.back().first - 1;
		}

		for (int j = 0; j < r; ++j) {
			int h = rht[j] - lft[j] - 1;

#ifdef DEBUG
			printf("%d by %d (%d)\n", h, 2 * (h + dp[j][i]));
#endif

			if(h != 0 && dp[j][i] != 0){
				maxx = max(maxx, 2 * (h + dp[j][i]));
			}
		}
	}

#ifdef DEBUG
		printf("dp: [\n");
		for(int i = 0; i < r; i++){
			printf("%d : ", i);
			for(int j = 0; j < c; j++){
				printf("%d, ", dp[i][j]);
			}
			printf("\n");
		}
		printf("]\n");
#endif

	printf("%d\n", maxx - 1);
}
